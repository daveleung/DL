#encoding: utf-8
import tensorflow as tf
import numpy as np
from data_utils import load_CIFAR10
#添加padding是为了strides为2时，尺寸是减小一半

_BATCH_NORM_DECAY = 0.997
_BATCH_NORM_EPSILON = 1e-5

def get_data(cifar10_dir):
    num_training = 49000
    num_validation = 1000
    num_test = 1000

    X_train, y_train, X_test, y_test = load_CIFAR10(cifar10_dir)
    # subsample the data
    # data format [N,W,H,C]
    mask = list(range(num_training, num_training + num_validation))
    X_val = X_train[mask]
    y_val = y_train[mask]
    mask = list(range(num_training))
    X_train = X_train[mask]
    y_train = y_train[mask]
    mask = list(range(num_test))
    X_test = X_test[mask]
    y_test = y_test[mask]

    # Normalize the data: subtract the mean image
    mean_image = np.mean(X_train, axis=0)
    X_train -= mean_image
    X_val -= mean_image
    X_test -= mean_image
    # X_dev -= mean_image

    # print('Train data shape: ', X_train.shape)
    # print('Train labels shape: ', y_train.shape)
    # print('Validation data shape: ', X_val.shape)
    # print('Validation labels shape: ', y_val.shape)
    # print('Test data shape: ', X_test.shape)
    # print('Test labels shape: ', y_test.shape)

    return X_train,y_train,X_test,y_test

def fixed_padding(inputs, kernel_size, data_format):
    """Pads the input along the spatial dimensions independently of input size.

    Args:
    inputs: A tensor of size [batch, channels, height_in, width_in] or
      [batch, height_in, width_in, channels] depending on data_format.
    kernel_size: The kernel to be used in the conv2d or max_pool2d operation.
                 Should be a positive integer.
    data_format: The input format ('channels_last' or 'channels_first').

    Returns:
    A tensor with the same format as the input with the data either intact
    (if kernel_size == 1) or padded (if kernel_size > 1).
    """
    pad_total = kernel_size - 1
    pad_beg = pad_total // 2
    pad_end = pad_total - pad_beg

    if data_format == 'channels_first':
        padded_inputs = tf.pad(inputs, [[0, 0], [0, 0],
                                        [pad_beg, pad_end], [pad_beg, pad_end]])
    else:
        padded_inputs = tf.pad(inputs, [[0, 0], [pad_beg, pad_end],
                                        [pad_beg, pad_end], [0, 0]])
    return padded_inputs

def conv2d_fixed_padding(inputs, filters, kernel_size, strides, data_format):
    """Strided 2-D convolution with explicit padding.

    The padding is consistent and is based only on `kernel_size`, not on the
    dimensions of `inputs` (as opposed to using `tf.layers.conv2d` alone).
    """
    if strides > 1:
        inputs = fixed_padding(inputs, kernel_size, data_format)
    #   print(inputs.shape)
    return tf.layers.conv2d(
      inputs=inputs, 
      filters=filters, 
      kernel_size=kernel_size,
      strides=strides,
      padding=('SAME' if strides == 1 else 'VALID'), 
      use_bias=False,
      kernel_initializer=tf.variance_scaling_initializer(),
      data_format=data_format
      )

def batch_norm_relu(inputs, is_training, data_format):
    """Performs a batch normalization followed by a ReLU."""
    # We set fused=True for a significant performance boost.
    # See https://www.tensorflow.org/performance/performance_guide#common_fused_ops
    inputs = tf.layers.batch_normalization(
      inputs=inputs, 
      axis=1 if data_format == 'channels_first' else 3,
      momentum=_BATCH_NORM_DECAY, 
      epsilon=_BATCH_NORM_EPSILON, 
      center=True,
      scale=True, 
      training=is_training,
      fused=True
    )
    inputs = tf.nn.relu(inputs)
    return inputs

def building_block(inputs, filters, is_training, projection_shortcut, strides,
                   data_format):
    """Standard building block for residual networks with BN before convolutions.

    Args:
    inputs: A tensor of size [batch, channels, height_in, width_in] or
      [batch, height_in, width_in, channels] depending on data_format.
    filters: The number of filters for the convolutions.
    is_training: A Boolean for whether the model is in training or inference
      mode. Needed for batch normalization.
    projection_shortcut: The function to use for projection shortcuts (typically
      a 1x1 convolution when downsampling the input).
    strides: The block's stride. If greater than 1, this block will ultimately
      downsample the input.
    data_format: The input format ('channels_last' or 'channels_first').

    Returns:
    The output tensor of the block.
    """
    shortcut = inputs
    inputs = batch_norm_relu(inputs, is_training, data_format)

    # The projection shortcut should come after the first batch norm and ReLU
    # since it performs a 1x1 convolution.
    if projection_shortcut is not None:
        shortcut = projection_shortcut(inputs)  #conv2d_fixed_padding

    inputs = conv2d_fixed_padding(
      inputs=inputs, 
      filters=filters, 
      kernel_size=3, 
      strides=strides,
      data_format=data_format)

    inputs = batch_norm_relu(
      inputs, 
      is_training, 
      data_format)

    inputs = conv2d_fixed_padding(
      inputs=inputs, 
      filters=filters, 
      kernel_size=3,
      strides=1,
      data_format=data_format)

    return inputs + shortcut

def block_layer(inputs, filters, block_fn, blocks, strides, is_training, name,
                data_format):
    """Creates one layer of blocks for the ResNet model.

    Args:
    inputs: A tensor of size [batch, channels, height_in, width_in] or
      [batch, height_in, width_in, channels] depending on data_format.
    filters: The number of filters for the first convolution of the layer.
    block_fn: The block to use within the model, either `building_block` or
      `bottleneck_block`.
    blocks: The number of blocks contained in the layer.
    strides: The stride to use for the first convolution of the layer. If
      greater than 1, this layer will ultimately downsample the input.
    is_training: Either True or False, whether we are currently training the
      model. Needed for batch norm.
    name: A string name for the tensor output of the block layer.
    data_format: The input format ('channels_last' or 'channels_first').

    Returns:
    The output tensor of the block layer.
    """
    # Bottleneck blocks end with 4x the number of filters as they start with
    #   filters_out = 4 * filters if block_fn is bottleneck_block else filters
    filters_out = filters

    def projection_shortcut(inputs):
        return conv2d_fixed_padding(
            inputs=inputs, 
            filters=filters_out, 
            kernel_size=1, 
            strides=strides,
            data_format=data_format)

    # Only the first block per block_layer uses projection_shortcut and strides
    inputs = block_fn(
        inputs, filters, 
        is_training, 
        projection_shortcut, 
        strides,                  
        data_format
    )

    for i in range(1, blocks):
        inputs = block_fn(
            inputs, 
            filters, 
            is_training, 
            None, 
            1, 
            data_format
        )

    return tf.identity(inputs, name)

def my_resnet(inputs, is_training, resnet_size, num_classes, data_format='channels_last'):

    if resnet_size % 6 != 2:
        raise ValueError('resnet_size must be 6n + 2:', resnet_size)
    num_blocks = (resnet_size - 2) // 6
    
    inputs = conv2d_fixed_padding(
        inputs=inputs, filters=16, kernel_size=3, strides=1,
        data_format=data_format)
    inputs = tf.identity(inputs, 'initial_conv')

    inputs = block_layer(
        inputs=inputs, filters=16, block_fn=building_block, blocks=num_blocks,
        strides=1, is_training=is_training, name='block_layer1',
        data_format=data_format)
    inputs = block_layer(
        inputs=inputs, filters=32, block_fn=building_block, blocks=num_blocks,
        strides=2, is_training=is_training, name='block_layer2',
        data_format=data_format)
    inputs = block_layer(
        inputs=inputs, filters=64, block_fn=building_block, blocks=num_blocks,
        strides=2, is_training=is_training, name='block_layer3',
        data_format=data_format)

    inputs = batch_norm_relu(inputs, is_training, data_format)
    inputs = tf.layers.average_pooling2d(
        inputs=inputs, pool_size=8, strides=1, padding='VALID',
        data_format=data_format)
    inputs = tf.identity(inputs, 'final_avg_pool')
    inputs = tf.reshape(inputs, [-1, 64])
    inputs = tf.layers.dense(inputs=inputs, units=num_classes) #全连接层？
    inputs = tf.identity(inputs, 'final_dense')
    
    return inputs     

def get_batch_data(batch_size,X_train,y_train):
#     train_data = tf.train.slice_input_producer([X_train, y_train], shuffle=False)
    image_batch, label_batch = tf.train.batch([X_train,y_train],batch_size = batch_size)
    return image_batch, label_batch

# image_batch, label_batch = get_batch_data()

# print(train_data[0].shape)
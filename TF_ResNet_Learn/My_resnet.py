import tensorflow as tf
import numpy as np
from data_utils import load_CIFAR10
import matplotlib.pyplot as plt
import math
from resnet_model import *

Not_use_model_flag = False
Train_set_dir = './cifar-10-batches-py'


# def get_CIFAR10_data(num_training=49000, num_validation=1000, num_test=1000, num_dev=500):
X_train,y_train,X_test,y_test = get_data(Train_set_dir)

### tf.reset_default_graph()
def build_graph():
    X = tf.placeholder(tf.float32, [None, 32, 32, 3])
    y = tf.placeholder(tf.int32, [None,])
    is_training = tf.placeholder(tf.bool)

    learning_rate = 0.1
    cla_score = my_resnet(X, is_training=True, resnet_size=20, num_classes=10, data_format='channels_last')
    cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=cla_score, labels=tf.one_hot(y,10)))
    optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(cost)

    #for test
    predict_y = y
    is_correct = tf.argmax(cla_score,axis = 1)
    is_correct = tf.equal(is_correct, tf.cast(predict_y, tf.int64))
    is_correct = tf.cast(is_correct, tf.float32)
    accuracy = tf.reduce_mean(is_correct)

    # save train model
    saver = tf.train.Saver()

    # train_value = (cost, optimizer, accuracy)
    # parameters = (X, y,saver)
    parameters = (X, y,saver,cost, optimizer, accuracy)
    return parameters

#Train ResNet
train_indicies = np.arange(X_train.shape[0])
# saver = tf.train.Saver()

# if Not_use_model_flag :
    # train_value, parameters= build_graph()
    # cost, optimizer, accuracy = train_value
    # X, y, saver = parameters
X, y, saver, cost, optimizer, accuracy = build_graph()
# else:
#     saver = tf.train.Saver()

with tf.Session() as sess:

    init = tf.global_variables_initializer()
    sess.run(init)

    if not Not_use_model_flag:
        print('use exist model')
        saver.restore(sess, "./Model/resnet20_model_2epoch.ckpt")

    batch_size = 100
    train_epochs = 30
    cost_history = []
    #Start Training
    for epoch in range(1,train_epochs+1):
        avg_cost = 0

        total_batch = int(math.ceil(X_train.shape[0]/batch_size))
        for iter in range(1,total_batch+1):
            start_idx = (iter*batch_size)%X_train.shape[0]
            idx = train_indicies[start_idx:start_idx+batch_size]
            feed_dict = {X: X_train[idx,:],y: y_train[idx]}
            c,_ = sess.run([cost, optimizer], feed_dict=feed_dict)
            cost_history.append(c)
            #Every 100 iteration print once
            if iter%100 == 0:
              train_acc = sess.run(accuracy, feed_dict=feed_dict)
              print("Epoch: [%d/%d], Iter: [%d/%d], cost: %f, train_acc:%f"%\
                    (epoch, train_epochs, iter, total_batch, c, train_acc))
        #One Epoch print once test accuracy
        if epoch%10 == 0:
            print("save %d epoch model."%epoch)
            saver.save(sess, "Model/resnet20_model_%depoch.ckpt"%epoch)
        #test model
        shuffle_num = int(np.ceil(np.abs(np.random.randn() * 100)))
        idx_test = train_indicies[shuffle_num:shuffle_num + batch_size]
        test_feed_dict = {X: X_test[idx_test, :], y: y_test[idx_test]}
        c,test_acc = sess.run([cost,accuracy], feed_dict=test_feed_dict)
        print("Epoch: %d,cost: %f, test_acc:%f"%\
              (epoch, c, test_acc))
#plot loss history
# plot(cost_history)
# plt.grid(True)
# plt.show()
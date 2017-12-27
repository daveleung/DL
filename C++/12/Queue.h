class Queue
{
	
private:
	//class scope definitions
	//Node is nested structure definition local to this class
	struct Node { Item item; struct Node * next;}
	enum {Q_size = 10};
	//private class members
	Node * front;
	Node * rear;
	int items;
	const int qsize;

public:
	Queue(int qs = Q_size);
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item &item);
	bool dequeue(Item &item);
};

Queue::Queue(int qs)
	: qise(qs),
	 front(NULL),
	 rear(NULL),
	 items(0)
{

}

bool Queue::enqueue(const Item & item)
{
	if (isfull())
		return false;
	Node * add = new Node;
	add->item = item;
	add->next = NULL;
	items++;
	if (front == NULL)
		front = add;
	else
		rear->next = add;
	rear = add;
	return true;
}

bool Queue::dequeue(Item & item)
{
	if (front == NULL)
		return false;
	item = front->item;
	items--;
	Node * temp = front;
	front = front->next;
	delete temp;
	if (items == 0)
		rear = NULL;
	return true;
}

Queue::~Queue()
{
	Node * temp;
	while (front != NULL)
	{
		temp = front;
		front = front->next;
		delete temp;
	}
}
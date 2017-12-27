#ifndef QUEUE_H_
#define QUEUE_H_
class Customer
{
private:
	long arrive;
	int processtime;
public:
	Customer() { arrive = processtime = 0;}
	void set(long when);
	long when() const { return arrive;}
	int ptime() const {return processtime;}
};

typedef Customer Item;
class Queue
{
private:
	//class scope definitions
	//node is a nested structure definition local to this c
	struct  Node { Item item; struct Node * next;};
	enum{Q_SIZE=10};
	//private clsss memners
	Node * front;
	Node * rear;
	int items;
	const int qsize;
	//preemptive definitions to prevent public copying
	Queue(const Queue & q) : qsize(0){}
	Queue & operator=(const Queue & q) { return *this;}
public:
	Queue(int qs = Q_SIZE);
	~Queue();
	bool isempty() const;
	bool isfull() const;
	int queuecount() const;
	bool enqueue(const Item &item);
	bool dequeue(Item &item);
};
#endif
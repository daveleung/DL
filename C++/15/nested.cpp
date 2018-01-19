#include <iostream>
#include <string>
#include "queuetp.h"

int main()
{
	using namespace std;
	 QueueTP<string> cs(5);

	 while(!cs.isfull())
	 {
	 	cout << "Please enter your name. You will be  "
	 			"served in the order of arrival.\n"
	 			"name: ";
	 	getline(cin, temp);
	 	cs.enqueue(temp);
	 }
	 cout << "The queue if full.Processing begins!\n";

	 while (!cs.isempty())
	 {
	 	cs.dequeue(temp);
	 	cout << "Now processing " << temp << "...\n";
	 }
	 return 0;
}
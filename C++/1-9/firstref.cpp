#include <iostream>
int main()
{
	using namespace std;
	int rats = 101;
	int & rodents = rats;
	cout << "rats = " << rats << endl;
	cout << "rodents = " << rodents << endl;

	cout << &rats << endl;
	cout << &rodents << endl;

	rats++;
	cout << rats << " " << rodents << endl;
}
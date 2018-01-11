#include <iostream>
#include "worker0.h"
using namespace std;

Worker::~Worker() {}

void Worker::Set()
{
	cout << "Enter worker's name: ";
	getline(cin, fullname);
	cout << "Enter worker's ID";
	cin >> id;
	while (cin.get() != '\n')
		continue;
}

void Worker::Show() const
{
	cout << "Name: " << fullname << "\n";
	cout << "Employee ID: " << id << "\n";

}

void Waiter::Set()
{
	Worker::Set();
	cout << "Enter waiter's panache rating: ";
	cin >> panache;
	while (cin.get() != '\n')
		continue;
}

void Waiter::Show() const
{
	cout << "Catefory: waiter\n";
	Worker::Show();
	cout << "panache rating: " << panache << "\n";
}

//Singer methods
char * Singer::pv[] = {"other", "alto", "contralto", "soprano", "brass", "baritone", "tenor"};

void Singer::Set()
{
	Worker::Set();
	cout << "Enter number for singer's vocal range:\n";
	int i;
	for (i = 0; i < Vtypes; i++)
	{
		cout << i << ": " << pv[i] << " ";
		if ( i % 4 == 3)
			cout << endl;

	}
	if ( i % 4 != 0)
		cout << endl;
	while (cin >> voice && (voice < 0 || voice >= Vtypes))
		cout << "Please enter a value >= 0 and < " << Vtypes << endl;

	while (cin.get() != '\n')
		continue;
}

void Singer::Show() const
{
	cout << "Catefory: singer\n";
	Worker::Show();
	cout << "Vocal range: " << pv[voice] << endl;
}
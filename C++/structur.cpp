#include <iostream>
struct inflateable
{
	char name[10];
	float volume;
	double price;
};

int main()
{
	using namespace std;

	inflateable guest =
	{
		"david",
		1.9,
		23.9
	};

	union one4all
	{
		int int_val;
		long long_val;
		double double_val;
	};

	one4all pail;
	pail.int_val = 5;
	cout << pail.int_val << endl;
	pail.double_val = 1.2;
	cout << pail.double_val << endl;


	cout << guest.name << endl;

	return 0;
}
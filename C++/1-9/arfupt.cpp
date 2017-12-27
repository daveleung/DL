#include <iostream>

const double *f1(const double ar[], int n);
const double *f2(const double [], int);
const double *f3(const double *, int);

int main()
{
	using namespace std;
	double av[3] = {112.3, 1542.6, 2227.9};

	const double *(*p1) (const double *, int) = f1;
	auto p2 = f2;

	cout << "Using pointers to functions:\n";
	cout << " Address Value\n";
	cout << (*p1)(av, 3) << ": " << *(*p1)(av, 3) << endl;
	cout << p2(av, 3) << ": " << *p2(av, 3) << endl;
}

const double * f1(const double *ar, int n)
{
	return ar;
}

const double * f2(const double ar[], int)
{
	return ar+1;
}

const double * f3(const double ar[], int)
{
	return ar+2;
}
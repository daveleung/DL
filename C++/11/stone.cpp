#include <iostream>
using std::cout;
#include "stonewt.h"

void display(const Stonewt & st, int n);

int main()
{
	Stonewt incognito;
	incognito = 275;
	Stonewt wolfe(23.5);
	Stonewt taft(21, 8);

	incognito.show_stn();

	cout << " wolfe: " ;
	wolfe.show_stn();
	return 0;
}

void display(const Stonewt & st, int n)
{

}
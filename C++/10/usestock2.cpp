#include <iostream>
#include "stock10.h"

int main()
{

	using std::cout;
	cout << "Using constructors to create new objects\n";
	Stock stock1("NanoSmart", 12, 20.0);
	stock1.show();
	Stock stock2 = Stock("Boffo", 2, 2.0);
	stock2.show();

	return 0;
}
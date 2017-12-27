#include <iostream>
#include "coordin.h"


int main()
{
	using namespace std;
	rect rplace;
	polar pplace;

	std::cout << "Enter the x and y values: ";
	while (std::cin >> rplace.x >> rplace.y)
	{
		pplace = rect_to_polar(rplace);
		show_polar(pplace);
		std::cout << "Next two numbers (q to quit): ";
	}

	std::cout << "Bye!\n";
	return 0;

}
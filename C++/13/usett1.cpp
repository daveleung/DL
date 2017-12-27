#include <iostream>
#include "tabtenn1.h"

int main(void)
{
	using std::cout;
	using std::endl;
	TableTennisPlayer palyer1("Tara", "Boomdea", false);
	RatedPlayer rplayer1(1140, "Mallory", "Duck", true);
	rplayer1.Name();
	if (rplayer1.HasTable())
		cout << ": has a table.\n";
	else 
		cout << ": hasn't a table.\n";

	palyer1.Name();
	if (palyer1.HasTable())
		cout << ": has a table.\n";
	else 
		cout << ": hasn't a table.\n";

	cout << "Name: ";
	rplayer1.Name();
	cout << "; Rating: " << rplayer1.Rating() << endl;
}
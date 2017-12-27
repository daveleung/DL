#include <iostream>
#include <cstring>
using std::cout;
using std::endl;
using std::string;
using std::cin;

int main()
{
// 	cout << name << ", please enter up to " << ArSize
// 	<< " short sayings <empty line to quit>:\n";
	string sayings[10];
	char temp[10];
	int i;
	cin.get(temp, 10);
	cout << cin.get() << endl;
	cout << temp << endl;


	// for (i = 0; i < 10; i++)
	// {
	// 	cout << i+1 << ": ";
	// 	cin.get(temp, 10);
	// 	cout << cin << endl;
	// 	cout << cin.get() << endl;
	// 	while(cin && cin.get() != '\n')
	// 	// 	cout << "test" << endl;
	// 		continue;
	// 	// if (!cin || temp[0] == '\n')
	// 	// 	break;
	// 	// else
	// 	// 	sayings[i] = temp;
	// }

	return 0;
}
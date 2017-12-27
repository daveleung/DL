#include <iostream>
int main()
{
	using namespace std;

	char ch;
	int count = 0;
	cout << "Enter characters; enter # to quit:\n";
	cin >> ch;
	// cout << ch << endl;
	while (ch != '#')
	{
		cout << ch << endl;
		++count;
		cin >> ch;
	}
	cout << endl << count << " characters read\n";
	return 0;
}
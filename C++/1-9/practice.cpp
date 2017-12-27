#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <array>
#include <stdio.h>
using namespace std;
char* getname();

struct inflatable
{
	char name[20];
	float volume;
	double price;
};
int main(int argc, char const *argv[])
{
	double al[4] = {1.2, 2.4, 5.6, 7.8};
	vector<doubel> a2(4);

	return 0;
}

char* getname()
{
	char temp[80];
	cout << "Enter last name: ";
	cin >> temp;
	char *pn = new char[strlen(temp) + 1];
	strcpy(pn, temp);

	return pn;
}
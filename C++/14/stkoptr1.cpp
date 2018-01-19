#include <iostream>
#include <cstdlib>
#include <ctime>
#include "stacktp1.h"
const int Num = 10;
int main()
{
	std::srand(std::time(0));
	std::cout << "please enter stack size.";
	int stacksize;
	std::cin >> stacksize;
	//create an empty stack with stacksize slots
	Stack<const char *> st(stacksize);

	//in basket
	const char * in[Num] = {
		" 1: Hank Gilgamesh", " 2: Kiki Ishtar",
		" 3: Betty Rocker", " 4: Ian Flagranti",
		" 5: Joy Almondo", " 6: Portia Koop",
		" 7: Wolfgan Kibble", " 8: Xaverie Paprika",
		" 9: Juan Moore", " 10: Misha Mache"
	};
	//out basket
	const char * out[Num];

	int processed = 0;
	int nextin = 0;
	while (processed < Num)
	{
		if (st.isempty())
			st.push(in[nextin++]);
		else if (st.isfull())
			st.pop(out[processed++]);
		else if (std::rand() % 2 && nextin < Num)
			st.push(in[nextin++]);
		else 
			st.pop(out[processed++]);
	}
	for (int i = 0; i < Num; i++)
		std::cout << out[i] << std::endl;
	std::cout << "Bye.\n";

	return 0;
}
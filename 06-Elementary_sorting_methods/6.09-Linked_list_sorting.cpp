#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <iomanip>

#include <Windows.h>

#include "../List.h"

void ex_6_15()
{
	auto link = generateRandList<int>(10, 9);

	printList(link);

	sort_list(link);

	printList(link);

	delete_list(link);
}

int main()
{
	for (size_t i = 0; i < 10000; ++i)
	{
		ex_6_15();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
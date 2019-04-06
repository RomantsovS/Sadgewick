#include <iostream>
#include <list>
#include <string>
#include <forward_list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <regex>
#include <random>
#include <conio.h>
#include <valarray>
#include <typeinfo>
#include <cctype>
#include <array>
#include <numeric>
#include <math.h>
#include <iomanip>

#include "List.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::forward_list;
using std::map;
using std::set;

void ex3_46()
{
	//std::srand(time(0));
	auto t = generateList(10, 0);

	printList(t);

	cout << "-----------------" << endl;

	while(t)
	{
		auto x = t;

		if (t->next)
		{
			t = t->next = t->next->next;
		}


		deleteNodeN(x);
	}

	printList(t);
}

void ex3_48()
{
	//std::srand(time(0));
	auto t = generateList(10, 0);

	printList(t);

	cout << "-----------------" << endl;

	size_t index = 1;

	auto x = t;
	link a = x, y;

	while (x)
	{
		if (!(index % 2))
		{
			y = x;
			x = a->next = x->next;
			//deleteNodeN(y);
			delete y;
		}
		else
		{
			a = x;
			x = x->next;
		}
		++index;
	}

	printList(t);

	while(t)
	{
		x = t;
		t = t->next;
		deleteNodeN(x);
	}
}

void ex3_49()
{
	auto t = generateCircularList(10, 0);

	printList(t);

	cout << "-----------------" << endl;

	auto x = t;

	while (x != next(x))
	{
		for(size_t i = 0; i < 5; ++i)
		{
			x = next(x);
		}
		deleteNodeN(remove(x));
	}

	printList(x);

	t = x;

	while (t)
	{
		t = x->next;
		deleteNodeN(x);
		t = nullptr;
	}
}

void ex3_50()
{
	size_t N = 10, M = 2;

	link t, x;
	size_t i;

	auto start_time = clock();

	construct(N);
	for (i = 2, x = newNode(1); i < N; ++i)
	{
		t = newNode(i);
		insert(x, t);
		x = t;
	}
	x = next(x);

	printList(x);

	while (x != next(x))
	{
		for (size_t i = 0; i < M; ++i)
		{
			x = next(x);
		}
		deleteNode(remove(x));
	}

	cout << "-----------------" << endl;

	cout << item(x) << endl;

	deleteNode(x);

	destruct();

	auto finish_time = clock();

	cout << "elasped time: " << static_cast<double>(finish_time - start_time) / CLOCKS_PER_SEC << endl;

	start_time = clock();

	t = generateCircularList(10, 0);

	printList(t);

	cout << "-----------------" << endl;

	x = t;

	while (x != next(x))
	{
		for (size_t i = 0; i < M; ++i)
		{
			x = next(x);
		}
		deleteNodeN(remove(x));
	}

	cout << item(x) << endl;

	deleteNodeN(x);

	finish_time = clock();

	cout << "elasped time: " << static_cast<double>(finish_time - start_time) / CLOCKS_PER_SEC << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex3_50();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
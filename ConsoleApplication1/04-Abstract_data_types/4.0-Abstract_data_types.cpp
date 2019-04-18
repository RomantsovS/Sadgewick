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

#include "../Point.h"
#include "../List.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

void ex_4_4()
{
	size_t N, cnt = 0, j;

	cout << "enter num points: ";
	cin >> N;

	vector<Point<float, 2>> points(N);

	for (size_t i = 0; i != N; ++i)
	{
		bool added = false;

		while (!added)
		{
			auto point = std::make_shared<Point<float, 2>>();
			point->InitRandom();

			bool finded = false;

			for (j = 0; j != cnt; ++j)
			{
				if (*point == points[j])
				{
					finded = true;
				}
			}

			if (!finded)
			{
				points[cnt] = *point;

				++cnt;

				added = true;
			}
		}
	}

	for (const auto &point : points)
	{
		cout << point;
	}
}

void ex_4_5()
{
	CList<int> list;

	size_t N = 9;

	for (size_t i = 0; i != N; ++i)
	{
		list.emplace(i);
	}

	list.print();

	auto ptr = list.get_head();

	while (ptr != ptr->next)
	{
		for (size_t i = 0; i != 3; ++i)
		{
			ptr = ptr->next;
		}
		list.remove(ptr);

		list.print();
	}
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_4_5();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
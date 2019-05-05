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

#include "../UF.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

struct pq
{
	size_t p, q;
};

void ex_4_29()
{
	const size_t N = 10;
	vector<pq> vec = { {3, 4}, {4, 9}, {8, 0}, {2, 3}, {5, 6}, {2, 9}, {5, 9}, {7, 3}, {4, 8}, {5, 6}, {0, 2}, {6, 1} };

	uf *info;

	info = new UFstruct(N);

	info->print();

	for (auto pair : vec)
	{
		//if (!info.find(pair.p, pair.q))
		{
			info->unite(pair.p, pair.q);

			cout << " " << pair.p << " " << pair.q << endl;
		}

		info->print();
	}
}

void ex_4_31()
{
	const size_t N = 10;
	vector<pq> vec = { {3, 4}, {4, 9}, {5, 6}, {0, 2}, {6, 1} };

	UF info(N);

	info.print();

	for (auto pair : vec)
	{
		info.unite(pair.p, pair.q);
		cout << " " << pair.p << " " << pair.q << endl;

		info.print();
	}

	for (auto pair : vec)
		cout << pair.p << " " << info.num_unioned_nodes(pair.p) << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_4_31();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
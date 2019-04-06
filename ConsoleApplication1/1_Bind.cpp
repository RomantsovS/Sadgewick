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

struct pq
{
	size_t p, q;
};

const size_t N = 1000;

void printLine(pq pair, size_t id[], size_t numIdUse);

int main()
{
	vector<pq> vec = { {3, 4}, {4, 9}, {8, 0}, {2, 3}, {5, 6}, {2, 9}, {5, 9}, {7, 3}, {4, 8}, {5, 6}, {0, 2}, {6, 1} };
	//vector<pq> vec = { {0, 2}, {1, 4}, {2, 5}, {3, 6}, {0, 4}, {1, 3}};
	//vector<pq> vec = { {0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}, {10, 11}, {12, 13}, {14, 15}, {0, 2}, {4, 6}, {8, 10}, {12, 14}, {0, 4}, {8, 12}, {0, 8} };
	//vector<pq> vec = { {0, 1}, {2, 3}, {4, 5}, {6, 7}, {8, 9}, {0, 2}, {4, 6}, {0, 4}, {6, 8} };

	std::vector<size_t> id(N);

	size_t i, totalIdUse = 0;
	size_t numIdUse = 0;

	/*cout << "fast find" << endl;
	cout << "p" << " q  ";

	for (i = 0; i < N; ++i)
	{
		id[i] = i;

		cout << i;

		if (i != N - 1)
			cout << " ";
	}

	cout << endl;	
		
	for (auto pair : vec)
	{
		totalIdUse += numIdUse;

		numIdUse = 0;

		int t = id[pair.p]; ++numIdUse;
		if (t == id[pair.q])
		{
			++numIdUse;
			printLine(pair, id, numIdUse);

			continue;
		}

		++numIdUse;

		for (i = 0; i != N; ++i)
		{
			if (id[i] == t) id[i] = id[pair.q];

			numIdUse += 3;
		}
		
		printLine(pair, id, numIdUse);
	}

	cout << "total id use: " << totalIdUse << endl;*/

	//////////////////////////////////////////////////////////////////////////quick-union
	int j;

	/*totalIdUse = 0;
	numIdUse = 0;

	cout << "quick-union" << endl;
	cout << "p" << " q  ";

	for (i = 0; i < N; ++i)
	{
		id[i] = i;

		cout << i;

		if (i != N - 1)
			cout << " ";
	}

	cout << endl;

	for (auto pair : vec)
	{
		totalIdUse += numIdUse;

		numIdUse = 0;

		for (i = pair.p; i != id[i]; i = id[i]); numIdUse += 2;
		for (j = pair.q; j != id[j]; j = id[j]); numIdUse += 2;
		if (i == j)
		{
			printLine(pair, id, numIdUse);

			continue;
		}

		id[i] = j; ++numIdUse;

		printLine(pair, id, numIdUse);
	}

	cout << "total id use: " << totalIdUse << endl;*/

	//////////////////////////////////////////////////////////////////////////weighted quick-union

	std::vector<size_t> sz(N);

	/*totalIdUse = 0;
	numIdUse = 0;

	cout << "weighted quick-union" << endl;
	cout << "p" << " q  ";

	for (i = 0; i < N; ++i)
	{
		id[i] = i;
		sz[i] = 1;

		cout << i;

		if (i != N - 1)
			cout << " ";
	}

	cout << endl;

	for (auto pair : vec)
	{
		totalIdUse += numIdUse;

		numIdUse = 0;

		for (i = pair.p; i != id[i]; i = id[i]); numIdUse += 2;
		for (j = pair.q; j != id[j]; j = id[j]); numIdUse += 2;
		if (i == j)
		{
			printLine(pair, id, numIdUse);

			continue;
		}

		if (sz[i] < sz[j])
		{
			id[i] = j; sz[j] += sz[i]; ++numIdUse;
		}
		else
			id[j] = i; sz[i] += sz[j]; ++numIdUse;

		printLine(pair, id, numIdUse);
	}

	cout << "total id use: " << totalIdUse << endl;*/

	//////////////////////////////////////////////////////////////////////////ex 1.20

	/*totalIdUse = 0;
	numIdUse = 0;

	cout << "ex 1.20" << endl;
	cout << "p" << " q  ";

	for (i = 0; i < N; ++i)
	{
		id[i] = i;
		sz[i] = 1;

		cout << i;

		if (i != N - 1)
			cout << " ";
	}

	cout << endl;

	for (auto pair : vec)
	{
		totalIdUse += numIdUse;

		numIdUse = 0;

		for (i = pair.p; i != id[i]; i = id[i]); numIdUse += 2;
		for (j = pair.q; j != id[j]; j = id[j]); numIdUse += 2;
		if (i == j)
		{
			printLine(pair, id, numIdUse);

			continue;
		}

		if (sz[i] < sz[j])
		{
			id[i] = j;

			++numIdUse;
		}
		else
		{
			id[j] = i;
			
			sz[i] = sz[j] + 1;

			++numIdUse;
		}

		printLine(pair, id, numIdUse);
	}

	cout << "total id use: " << totalIdUse << endl;*/

	//////////////////////////////////////////////////////////////////////////weighted quick-union with path compression by halving

	/*totalIdUse = 0;
	numIdUse = 0;

	cout << "weighted quick-union with path compression by halving" << endl;
	cout << "p" << " q  ";

	for (i = 0; i < N; ++i)
	{
		id[i] = i;
		sz[i] = 1;

		cout << i;

		if (i != N - 1)
			cout << " ";
	}

	cout << endl;

	for (auto pair : vec)
	{
		totalIdUse += numIdUse;

		numIdUse = 0;

		for (i = pair.p; i != id[i]; i = id[i])
		{
			id[i] = id[id[i]]; numIdUse += 2;
		}
		for (j = pair.q; j != id[j]; j = id[j])
		{
			id[j] = id[id[j]]; numIdUse += 2;; numIdUse += 2;
		}

		if (i == j)
		{
			printLine(pair, id, numIdUse);

			continue;
		}

		if (sz[i] < sz[j])
		{
			id[i] = j; sz[j] += sz[i]; ++numIdUse;
		}
		else
			id[j] = i; sz[i] += sz[j]; ++numIdUse;

		printLine(pair, id, numIdUse);
	}

	cout << "total id use: " << totalIdUse << endl;*/

	/////////////////////////////////////////////////////////////////////ex 1.22

	totalIdUse = 0;
	numIdUse = 0;
	size_t num_edges;

	cout << "ex 1.22" << endl;
	//cout << "p" << " q  ";

	for (size_t n = 100; n <= N; n+=10)
	{
		for (i = 0; i < n; ++i)
		{
			id[i] = i;
			sz[i] = 1;

			/*cout << i;

			if (i != N - 1)
				cout << " ";*/
		}

		//cout << endl;

		std::default_random_engine rand_eng;
		std::uniform_int_distribution<size_t> u_h(0, n - 1);

		num_edges = 0;

		for (size_t t = 0; t != n; ++t)
		{
			pq pair = { u_h(rand_eng), u_h(rand_eng) };

			totalIdUse += numIdUse;

			numIdUse = 0;

			for (i = pair.p; i != id[i]; i = id[i])
			{
				id[i] = id[id[i]]; numIdUse += 2;
			}
			for (j = pair.q; j != id[j]; j = id[j])
			{
				id[j] = id[id[j]]; numIdUse += 2;; numIdUse += 2;
			}

			if (i == j)
			{
				//printLine(pair, id, numIdUse);

				continue;
			}

			if (sz[i] < sz[j])
			{
				id[i] = j; sz[j] += sz[i]; ++numIdUse;
			}
			else
				id[j] = i; sz[i] += sz[j]; ++numIdUse;

			num_edges++;

			//printLine(pair, id, numIdUse);
		}

		//cout << "total id use: " << totalIdUse << endl;
		cout.width(4);
		cout << n << " " << string(num_edges / 10, '*') << endl;
	}

	//////////////////////////////////////////////////////////////////////////ex 1.16

	/*totalIdUse = 0;
	numIdUse = 0;

	cout << "ex 16" << endl;
	cout << "p" << " q  ";

	for (i = 0; i < N; ++i)
	{
		id[i] = i;
		sz[i] = 1;

		cout << i;

		if (i != N - 1)
			cout << " ";
	}

	cout << endl;

	for (auto pair : vec)
	{
		totalIdUse += numIdUse;

		numIdUse = 0;

		for (i = pair.p; i != id[i]; i = id[i])
		{//id[i] = id[id[i]]; numIdUse += 2;; numIdUse += 2;
			for (; id[i] != id[id[i]]; id[i] = id[id[i]]) numIdUse += 6;
		}

		numIdUse += 2;

		for (j = pair.q; j != id[j]; j = id[j])
		{//id[j] = id[id[j]]; numIdUse += 2;; numIdUse += 2;
			for (; id[j] != id[id[j]]; id[j] = id[id[j]]) numIdUse += 6;
		}

		numIdUse += 2;

		if (i == j)
		{
			printLine(pair, id, numIdUse);

			continue;
		}

		if (sz[i] < sz[j])
		{
			id[i] = j; sz[j] += sz[i]; ++numIdUse;
		}
		else
			id[j] = i; sz[i] += sz[j]; ++numIdUse;

		printLine(pair, id, numIdUse);
	}

	cout << "total id use: " << totalIdUse << endl;*/

	cout << "press any key to exit\n";
	_getch();

	return 0;
}

void printLine(pq pair, size_t id[], size_t numIdUse)
{
	cout << pair.p << " " << pair.q << "  ";

	for (size_t i = 0; i != N; ++i)
	{
		cout << *(id + i) << " ";
	}

	cout << "\tid use: " << numIdUse << endl;
}
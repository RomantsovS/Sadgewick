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

struct node
{
	node(int x, node *t = nullptr) : item(x), next(t) {}

	int item;
	node *next;
};

using link = node *;

void printList(link t)
{
	auto x = t;

	do
	{
		cout << x->item << endl;

		x = x->next;
	} while (x != t && x);
}

link generateList(size_t len, int start)
{
	link t = new node(start, 0);

	link x = t;

	for (size_t i = 1; i < len; ++i)
	{
		x = (x->next = new node(start + i, 0));
	}

	return t;
}

link generateCircularList(size_t len, int start)
{
	link t = new node(start, 0);

	link x = t;

	for (size_t i = 1; i < len; ++i)
	{
		x = (x->next = new node(start + i));
	}

	x->next = t;

	return t;
}

size_t f_ex3_23(const link t)
{
	link x = t;
	size_t cnt = 0;

	while (x->next != t)
	{
		++cnt;
		x = x->next;
	}

	return cnt;
}

size_t f_ex3_24(const link x, const link t)
{
	link tmp = x;
	size_t cnt = 0;

	while (tmp->next != t)
	{
		++cnt;
		tmp = tmp->next;
	}

	return cnt;
}

void ex3_24()
{
	const unsigned long M = 5, N = 9;

	link t = new node(1, 0);
	t->next = t;

	link x = t;

	for (size_t i = 2; i <= N; ++i)
	{
		x = (x->next = new node(i, t));
	}

	printList(t);

	cout << "--------------" << endl;

	cout << f_ex3_24(x, t->next) << endl;
}

void ex3_25()
{
	const unsigned long N = 9;

	auto t = generateList(N, 0);
	auto t2 = generateList(N, N);

	printList(t);
	cout << "--------------" << endl;
	printList(t2);
	cout << "--------------" << endl;

	auto x = t2->next;

	t2->next = t;

	while (t->next)
	{
		t = t->next;
	}

	t->next = x;

	printList(t2);
}

void ex3_26()
{
	const unsigned long N = 9;

	auto t = generateCircularList(N, 0);
	auto t2 = generateCircularList(N, N);

	printList(t);
	cout << "--------------" << endl;
	printList(t2);
	cout << "--------------" << endl;

	auto x = t2->next;

	t2->next = t->next;

	t2->next->next = x;

	printList(t2);
}

void ex3_29()
{
	const unsigned long M = 5, N = 10;

	for (size_t n = 9; n < N; n += static_cast<unsigned long>(std::ceil(N / 10.0)))
	{
		auto t = generateCircularList(n, 1);

		//printList(t);
		//cout << "--------------" << endl;

		auto x = t;

		while (x != x->next)
		{
			for (size_t i = 1; i != M; ++i)
			{
				x = x->next;
			}

			x->next = x->next->next;
		}

		cout << std::setw(3) << n << " " << x->item << " ";

		for (size_t j = 0; j < static_cast<size_t>(x->item); j += static_cast<unsigned long>(std::ceil(n / 10.0)))
			cout << "*";
		cout << endl;
	}
}

void printMas(int *mas, size_t len)
{
	for (size_t i = 0; i != len; ++i)
	{
		cout << mas[i] << " ";
	}
	cout << endl;
}

void ex3_30()
{
	const unsigned long M = 5, N = 9;

	int *masItem = new int[N];
	int *next = new int[N];

	size_t i;

	for (i = 1; i <= N; ++i)
	{
		masItem[N - i] = i;
		
		if(i == N)
			next[N - i] = N - 1;
		else
			next[N - i] = N - i - 1;
	}

	printMas(masItem, N);
	cout << "--------------" << endl;

	printMas(next, N);

	auto x = 0;

	while (x != next[x])
	{
		for (size_t i = 1; i != M; ++i)
		{
			x = next[x];
		}

		next[x] = next[next[x]];

		printMas(next, N);
	}
	cout << masItem[x] << endl;;
}

int main()
{
	ex3_29();
	ex3_30();

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
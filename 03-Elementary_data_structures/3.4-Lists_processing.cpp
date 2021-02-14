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
	node() : next(nullptr) {}
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

void printListWithHead(link head)
{
	printList(head->next);
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

link generateRandList(size_t len, size_t max_val)
{
	link t = new node(rand() % max_val, 0);

	link x = t;

	for (size_t i = 1; i < len; ++i)
	{
		x = (x->next = new node(rand() % max_val, 0));
	}

	return t;
}

link generateRandListWithHead(size_t len, size_t max_val)
{
	link head = new node();
	
	link t = new node(rand() % max_val, 0);
	head->next = t;

	link x = t;

	for (size_t i = 1; i < len; ++i)
	{
		x = (x->next = new node(rand() % max_val, 0));
	}

	return head;
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

void inverse_list(link &x)
{
	link r = 0, y = x, t;

	while (y)
	{
		t = y->next;

		y->next = r;

		r = y;

		y = t;
	}

	x = r;
}

void sort_list(link &a)
{
	link b = new node(a->item), x, u, t;

	for (t = a->next; t != 0; t = u)
	{
		u = t->next;
		bool inserted = false;

		for (x = b; x->next; x = x->next)
		{
			if (x->item > t->item)
			{
				t->next = x;
				
				if (x == b)
					b = t;

				inserted = true;
				break;
			}
			else if(x->next->item > t->item)
			{
				break;
			}
		}

		if (!inserted)
		{
			t->next = x->next;
			x->next = t;
		}
	}

	a = b;
}

void sort_list_with_head(link &a)
{
	link b = new node(0), x, u, t;

	for(t = a->next; t != 0; t = u)
	{
		u = t->next;

		for (x = b; x->next != 0; x = x->next)
		{
			if (x->next->item > t->item)
				break;
		}

		t->next = x->next;
		x->next = t;
	}

	a = b;
}

void ex3_31()
{
	auto t = generateRandList(10, 1000);

	printList(t);

	cout << "-----------------" << endl;

	sort_list(t);

	printList(t);
}

void ex3_33_f(link &a)
{
	link t = a, max_node = a, prev = a;
	int max = t->item;

	for(; t->next; t = t->next)
	{
		if (t->item > max)
		{
			max = t->item;
			max_node = t;

			while (prev->next != t)
				prev = prev->next;
		}
	}

	prev->next = max_node->next;
	t->next = max_node;
	max_node->next = nullptr;
}

void ex3_33()
{
	auto t = generateRandList(10, 1000);

	printList(t);

	cout << "-----------------" << endl;

	ex3_33_f(t);

	printList(t);
}

void ex3_34_f(link &a)
{
	link t = a, min_node = a, prev = a;
	int min = t->item;

	for(; t->next; t = t->next)
	{
		if (t->item < min)
		{
			min = t->item;
			min_node = t;

			while (prev->next != t)
				prev = prev->next;
		}
	}

	if (min_node != a)
	{
		prev->next = min_node->next;
		min_node->next = a;
		a = min_node;
	}

}

void ex3_34()
{
	std::srand(static_cast<unsigned>(time(0)));
	auto t = generateRandList(10, 1000);

	printList(t);

	cout << "-----------------" << endl;

	ex3_34_f(t);

	printList(t);
}

void ex3_35_f(link &a)
{
	link t = a->next->next, uneven = a, even = a->next, last_even = even, last_uneven = uneven;
	size_t cnt = 1;

	for (; t; t = t->next)
	{
		if (cnt % 2)
		{
			last_uneven = (last_uneven->next = t);
		}
		else
		{
			last_even = (last_even->next = t);
		}

		++cnt;
	}

	last_uneven->next = even;
	last_even->next = nullptr;

	a = uneven;
}

void ex3_35()
{
	//std::srand(time(0));
	auto t = generateRandList(10, 1000);

	printList(t);

	cout << "-----------------" << endl;

	ex3_35_f(t);

	printList(t);
}

void ex3_36_f(link &t, link &u)
{
	auto t_next = t->next;

	t->next = u->next;
	
	auto x = u->next->next;
	u->next->next = t_next->next;

	u->next = t_next;
	t_next->next = x;
}

void ex3_36()
{
	auto t = generateList(10, 0);

	printList(t);

	cout << "-----------------" << endl;

	ex3_36_f(t->next, t->next->next->next);

	printList(t);
}

link ex3_37_f(const link &t)
{
	link start = new node(t->item);
	auto x = start;

	auto y = t->next;
	while (y)
	{
		x = (x->next = new node(y->item));
		y = y->next;
	}

	return start;
}

void ex3_37()
{
	auto t = generateList(10, 0);

	printList(t);

	cout << "-----------------" << endl;

	auto x = ex3_37_f(t);

	printList(x);
}

bool ex3_38_f2(link t)
{
	return t && t->item > 2 && (t->item % 2);
}

void ex3_38_f(link &t, bool(*f)(link))
{
	auto x = t;

	while (x->next)
	{
		if (!f(t))
			t = x = t->next;
		else
		{
			if (!f(x->next))
			{
				x->next = x->next->next;
			}
			else
				x = x->next;
		}
	}
}

void ex3_38()
{
	auto t = generateList(10, 0);

	printList(t);

	cout << "-----------------" << endl;

	ex3_38_f(t, ex3_38_f2);

	printList(t);
}

link ex3_39_f(const link t, bool(*f)(link))
{
	std::remove_const<decltype(t)>::type x = nullptr, y, start = nullptr;

	for(y = t; y; y = y->next)
	{
		if (f(y))
		{			
			if (!start)
			{
				start = x = new node(y->item);
			}
			else
			{
				auto tmp = new node(y->item);
				x = x->next = tmp;
			}
		}
	}

	return start;
}

void ex3_39()
{
	auto t = generateList(10, 0);

	printList(t);

	cout << "-----------------" << endl;

	auto x = ex3_39_f(t, ex3_38_f2);

	printList(x);

	cout << "-----------------" << endl;

	printList(t);
}

void inverse_list_with_head(link &x)
{
	auto start = x;

	x = x->next;

	inverse_list(x);

	start->next = x;

	x = start;
}

void ex3_40()
{
	auto t = generateRandListWithHead(10, 100);

	printListWithHead(t);

	cout << "-----------------" << endl;

	inverse_list_with_head(t);

	printListWithHead(t);
}

void ex3_41()
{
	auto t = generateRandList(10, 100);

	printList(t);

	cout << "-----------------" << endl;

	sort_list(t);

	printList(t);
}

void ex3_42()
{
	auto t = generateRandListWithHead(9, 100);

	printListWithHead(t);

	cout << "-----------------" << endl;

	const int M = 5;

	auto x = t;

	while (x->next)
	{
		for (int i = 1; i < M; ++i)
		{
			if (!x->next)
				x = t;
			else
				x = x->next;
		}

		if (!x->next)
			x = t->next = t->next->next;
		else
			x->next = x->next->next;

		printListWithHead(t);
		cout << "-----------------" << endl;
	}

	cout << x->item << endl;
}

int main()
{
	ex3_42();

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
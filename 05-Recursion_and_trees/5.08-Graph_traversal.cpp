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

#include "../List.h"
#include "../Stack.h"
#include "../Queue.h"

const size_t V = 10;
bool visited[V];
CList<int> adv[V];

void print(int i)
{
	cout << i << "->";

	auto cur_list = adv[i];

	if (cur_list.empty())
	{
		cout << endl;
		return;
	}

	auto ptr = cur_list.get_head();

	do
	{
		cout << ptr->item << "->";
		ptr = ptr->next;
	} while (ptr != cur_list.get_head());

	cout << endl;
}

void depth_first_search(int k, void visit(int))
{
	visit(k);

	visited[k] = true;

	auto t = adv[k].get_head();

	do
	{
		if (!visited[t->item])
			depth_first_search(t->item, visit);
		t = t->next;
	} while (t != adv[k].get_head());
}

void width_first_search(int k, void visit(int))
{
	QueueList<int> st;

	st.put(k);

	while (!st.empty())
	{
		if (!visited[k = st.get()])
		{
			visit(k);

			visited[k] = true;

			auto t = adv[k].get_head();

			do
			{
				if (!visited[t->item])
					st.put(t->item);

				t = t->next;
			} while (t != adv[k].get_head());
		}
	}
}

void ex_5_98()
{
	int i, j;
	std::vector<int> ivec = { 0, 2, 1, 4, 2, 5, 3, 6, 0, 4, 6, 0, 1, 3 };

	for (auto iter = ivec.cbegin(); iter != ivec.cend(); ++iter)
	{
		i = *iter;
		j = *(++iter);

		adv[i].emplace(j);
		adv[j].emplace(i);
	}

	for (i = 0; i != V; ++i)
	{
		print(i);
	}

	cout << "=======\n";

	StackList<int> st(10);

	int k = 0;

	st.push(k);

	while (!st.empty())
	{
		if (!visited[k = st.pop()])
		{
			print(k);

			visited[k] = true;

			auto t = adv[k].get_head();

			do
			{
				if (!visited[t->item])
					st.push(t->item);

				t = t->next;
			} while (t != adv[k].get_head());
		}
	}

	cout << "=======\n";

	for (auto &t : visited)
		t = 0;

	width_first_search(0, print);
}

void ex_5_99()
{
	int i, j;
	std::vector<int> ivec = { 0, 2, 1, 4, 2, 5, 3, 6, 0, 4, 6, 0, 1, 3 };

	for(auto iter = ivec.cbegin(); iter != ivec.cend(); ++iter)
	{
		i = *iter;
		j = *(++iter);

		adv[i].emplace(j);
		adv[j].emplace(i);
	}

	for (i = 0; i != V; ++i)
	{
		print(i);
	}

	cout << "=======\n";

	depth_first_search(0, print);
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_5_98();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
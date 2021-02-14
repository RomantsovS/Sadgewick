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
#include <stack>
#include <queue>
#include <ctime>

#include "../Tree.h"

template <typename T>
void visit(T node)
{
	cout << node->item;
}

template <typename T>
void traverse_forward_recursive(T node)
{
	if (!node)
		return;

	visit(node);

	traverse_forward_recursive(node->l);
	traverse_forward_recursive(node->r);
}

template <typename T>
void traverse_forward(T node)
{
	std::stack<T> s;

	s.push(node);

	while (!s.empty())
	{
		node = s.top();
		visit(node);
		s.pop();
		
		if (node->r)
			s.push(node->r);
		if (node->l)
			s.push(node->l);
	}
}

void ex_5_15()
{
	auto tree = CTree<char>('E', 1);

	auto node = tree.find_node('E');
	auto nodeD = tree.add_val('D', node, true);
	auto nodeB = tree.add_val('B', nodeD, true);
	tree.add_val('A', nodeB, true);
	nodeB = tree.find_node('B');
	tree.add_val('C', nodeB, false);

	auto nodeH = tree.add_val('H', node, false);
	auto nodeF = tree.add_val('F', nodeH, true);
	tree.add_val('G', nodeF, false);

	tree.print(tree.get_root(), 2);

	cout << "===================\n";

	traverse_forward(tree.get_root());

	cout << endl;
}

template <typename T>
void traverse_levels(T node)
{
	std::queue<T> s;

	s.push(node);

	while (!s.empty())
	{
		node = s.front();
		visit(node);
		s.pop();

		if (node->l)
			s.push(node->l);
		if (node->r)
			s.push(node->r);
	}
}

void ex_5_16()
{
	auto tree = CTree<char>('E', 1);

	auto node = tree.find_node('E');
	auto nodeD = tree.add_val('D', node, true);
	auto nodeB = tree.add_val('B', nodeD, true);
	tree.add_val('A', nodeB, true);
	nodeB = tree.find_node('B');
	tree.add_val('C', nodeB, false);

	auto nodeH = tree.add_val('H', node, false);
	auto nodeF = tree.add_val('F', nodeH, true);
	tree.add_val('G', nodeF, false);

	tree.print(tree.get_root(), 2);

	cout << "===================\n";

	traverse_levels(tree.get_root());

	cout << endl;
}

template <typename T>
void ex_5_82_f(T node)
{
	std::stack<T> s;

	while (!s.empty() || node)
	{
		if (node)
		{
			s.push(node);
			node = node->l;
		}
		else
		{
			node = s.top();
			s.pop();
			visit(node);
			node = node->r;
		}
	}
}

template <typename T>
void ex_5_82_f_2(T node)
{
	std::stack<T> s;

	decltype(node) cur_node = node;

	while (!s.empty() || cur_node)
	{
		if (cur_node)
		{
			if (cur_node->r)
				s.push(cur_node->r);

			s.push(cur_node);

			cur_node = cur_node->l;
		}
		else
		{
			auto tmp_node = s.top();
			s.pop();

			visit(tmp_node);

			if (!s.empty() && tmp_node->r == s.top())
			{
				cur_node = s.top();
				s.pop();
			}
		}
	}
}

void ex_5_82()
{
	/*auto tree = CTree<char>('E', 1);

	auto node = tree.find_node('E');
	auto nodeD = tree.add_val('D', node, true);
	auto nodeB = tree.add_val('B', nodeD, true);
	tree.add_val('A', nodeB, true);
	nodeB = tree.find_node('B');
	tree.add_val('C', nodeB, false);

	auto nodeH = tree.add_val('H', node, false);
	auto nodeF = tree.add_val('F', nodeH, true);
	tree.add_val('G', nodeF, false);*/

	srand(static_cast<unsigned>(time(0)));

	auto tree = generate_tree_random<char>(120, 'A', 'Z' - 'A');
	tree.print(tree.get_root(), 2);

	cout << "===================\n";

	auto start_time = clock();
	for (size_t i = 0; i != 1000; ++i)
		ex_5_82_f(tree.get_root());
	cout << endl;
	auto end_time = clock();

	cout << end_time - start_time << endl;

	start_time = clock();
	for(size_t i = 0; i != 1000; ++i)
		ex_5_82_f_2(tree.get_root());
	cout << endl;
	end_time = clock();

	cout << end_time - start_time << endl;

	cout << endl;
}

template <typename T>
void ex_5_83_f(T node)
{
	std::stack<T> s;

	decltype(node) last_node = nullptr;

	while (!s.empty() || node)
	{
		if (node)
		{
			s.push(node);

			node = node->l;
		}
		else
		{
			auto tmp_node = s.top();
			if (tmp_node->r && last_node != tmp_node->r)
				node = tmp_node->r;
			else
			{
				visit(tmp_node);
				s.pop();
				last_node = tmp_node;
			}
		}
	}
}

template <typename T>
void ex_5_83_f_2(T node)
{
	std::stack<T> s;

	decltype(node) cur_node = node;

	while (!s.empty() || cur_node)
	{
		if (cur_node)
		{
			s.push(cur_node);

			if (cur_node->r)
				s.push(cur_node->r);

			cur_node = cur_node->l;
		}
		else
		{
			auto tmp_node = s.top();
			s.pop();

			visit(tmp_node);

			if (!s.empty() && s.top()->r != tmp_node && s.top()->l != tmp_node)
			{
				cur_node = s.top();
				s.pop();
			}
		}
	}
}

void ex_5_83()
{
	auto tree = CTree<char>('E', 1);

	auto node = tree.find_node('E');
	auto nodeD = tree.add_val('D', node, true);
	auto nodeB = tree.add_val('B', nodeD, true);
	tree.add_val('A', nodeB, true);
	nodeB = tree.find_node('B');
	tree.add_val('C', nodeB, false);

	auto nodeH = tree.add_val('H', node, false);
	auto nodeF = tree.add_val('F', nodeH, true);
	tree.add_val('G', nodeF, false);

	tree.print(tree.get_root(), 2);

	cout << "===================\n";

	ex_5_83_f(tree.get_root());

	cout << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_5_83();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
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

#include "../Tree.h"

void ex_5_86()
{
	std::vector<char> ivec = { 'a', 'g', 'h', 't', 'y' };

	auto tree = generate_tree_max<char>(ivec);

	tree.print(tree.get_root(), 0);

	cout << tree.num_nodes(tree.get_root()) << endl;
	cout << tree.height(tree.get_root()) << endl;
	cout << tree.num_leaves(tree.get_root()) << endl;
}

void ex_5_88()
{
	std::vector<char> ivec;

	for (size_t i = 0; i != 20; ++i)
		ivec.push_back('A' + rand() % 24);

	auto tree = generate_tree_max<char>(ivec);

	tree.print(tree.get_root(), 0);

	cout << tree.internal_path_lenght(tree.get_root(), 0) << endl;
}

std::shared_ptr<CTree<char>::node<char>> erase(std::shared_ptr<CTree<char>::node<char>> node, char val)
{
	if (!node)
		return node;

	if (node->item == val)
	{
		if (node->l && node->l->item == val)
		{
			if (node->r)
			{
				node->item = node->r->item;
			}

			if (node->l->l || node->l->r)
				node->l = erase(node->l, val);
			else
				node->l = nullptr;
		}
		else if (node->r && node->r->item == val)
		{
			if (node->l)
			{
				node->item = node->l->item;
			}

			if (node->r->l || node->r->r)
				node->r = erase(node->r, val);
			else
				node->r = nullptr;
		}
		else
			node = nullptr;
	}
	else
	{
		node->l = erase(node->l, val);
		node->r = erase(node->r, val);
	}

	return node;
}

void ex_5_91()
{
	std::vector<char> ivec;

	for (size_t i = 0; i != 10; ++i)
		ivec.push_back('A' + rand() % 26);

	auto tree = generate_tree_max<char>(ivec);

	tree.print(tree.get_root(), 0);

	cout << "===================\n";

	tree.get_root() = erase(tree.get_root(), 'Y');

	tree.print(tree.get_root(), 0);
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_5_91();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
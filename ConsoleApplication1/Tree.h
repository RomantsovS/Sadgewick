#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <memory>

using std::cout;
using std::cin;
using std::endl;

template<typename T>
class CTree
{
public:
	template<typename T>
	struct node
	{
		node() : l(nullptr), r(nullptr) {}
		node(T x, std::shared_ptr<node> _l = nullptr, std::shared_ptr<node> _r = nullptr) :
			item(x), l(_l), r(_r) {}

		T item;
		std::shared_ptr<node> l, r;
	};

	CTree(std::shared_ptr<node<T>> _root = nullptr) : root(_root) {}

	std::shared_ptr<node<T>> &get_root()
	{
		return root;
	}

	bool empty() const;

	std::shared_ptr<node<T>> l(std::shared_ptr<node<T>> t)
	{
		return t->l;
	}

	std::shared_ptr<node<T>> r(std::shared_ptr<node<T>> t)
	{
		return t->r;
	}

	void print(std::shared_ptr<node<T>> curr_ptr, size_t h) const;

	size_t num_nodes(std::shared_ptr<node<T>> cur_node) const;
	int height(std::shared_ptr<node<T>> cur_node) const;

	size_t num_leaves(std::shared_ptr<node<T>> cur_node) const;

	size_t internal_path_lenght(std::shared_ptr<node<T>> cur_node, size_t h) const;
private:
	std::shared_ptr<node<T>> root;

	void print_node(T item, size_t h) const;
};

template<typename T>
inline bool CTree<T>::empty() const
{
	return !root;
}

template<typename T>
void CTree<T>::print(std::shared_ptr<node<T>> curr_node, size_t h) const
{
	if (!curr_node)
	{
		//print_node('*', h);
		return;
	}

	print_node(curr_node->item, h);

	if (!curr_node->l && !curr_node->r)
		cout << '-' << endl;
	else
	{
		cout << endl;
		print(curr_node->l, h + 1);
		print(curr_node->r, h + 1);
	}
}

template<typename T>
size_t CTree<T>::num_nodes(std::shared_ptr<node<T>> cur_node) const
{
	if (!cur_node)
		return 0;
	return num_nodes(cur_node->l) + num_nodes(cur_node->r) + 1;
}

template<typename T>
int CTree<T>::height(std::shared_ptr<node<T>> cur_node) const
{
	if (!cur_node)
		return -1;

	int u = height(cur_node->l), v = height(cur_node->r);

	if (u > v)
		return u + 1;
	else
		return v + 1;
}

template<typename T>
size_t CTree<T>::num_leaves(std::shared_ptr<node<T>> cur_node) const
{
	if (!cur_node)
		return 0;
	else if (!cur_node->l && !cur_node->r)
		return 1;

	return num_leaves(cur_node->l) + num_leaves(cur_node->r);
}

template<typename T>
size_t CTree<T>::internal_path_lenght(std::shared_ptr<node<T>> cur_node, size_t h) const
{
	if (!cur_node)
		return 0;
	if (cur_node->l || cur_node->r)
		return h + internal_path_lenght(cur_node->l, h + 1) + internal_path_lenght(cur_node->r, h + 1);
	return 0;
}

template<typename T>
void CTree<T>::print_node(T item, size_t h) const
{
	for (size_t i = 0; i != h; ++i)
		cout << ' ';
	cout << item;
}

#endif
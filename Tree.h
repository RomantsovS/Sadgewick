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
	CTree(const T first_val, const size_t size);

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

	std::shared_ptr<CTree<T>::node<T>> add_val(const T val);
	std::shared_ptr<CTree<T>::node<T>> add_val(const T val, std::shared_ptr<CTree<T>::node<T>> dest, bool left);
	const std::shared_ptr<CTree<T>::node<T>> find_node(const T val, const std::shared_ptr<CTree<T>::node<T>> start_node = nullptr) const;

	std::shared_ptr<CTree<T>::node<T>> get_rand_node();

	void print(std::shared_ptr<node<T>> curr_ptr, size_t offset, size_t start_offset = 0) const;

	size_t num_nodes(std::shared_ptr<node<T>> cur_node) const;
	int height(std::shared_ptr<node<T>> cur_node) const;

	size_t num_leaves(std::shared_ptr<node<T>> cur_node) const;

	size_t internal_path_lenght(std::shared_ptr<node<T>> cur_node, size_t h) const;
private:
	std::shared_ptr<node<T>> root;

	void print_node(T item, size_t offset) const;

	std::pair<size_t, std::shared_ptr<node<T>>> get_shortest_node(std::shared_ptr<node<T>> cur_node = nullptr);
};

template<typename T>
inline CTree<T>::CTree(const T first_val, const size_t size)
{
	for (size_t i = 0; i != size; ++i)
		add_val(first_val + static_cast<T>(i));
}

template<typename T>
inline bool CTree<T>::empty() const
{
	return !root;
}

template<typename T>
inline std::shared_ptr<CTree<T>::node<T>> CTree<T>::add_val(const T val)
{
	if (!root)
	{
		root = std::make_shared<CTree<T>::node<T>>(val);
		return root;
	}

	auto node = get_shortest_node(root);

	if (!node.second->l)
	{
		node.second->l = std::make_shared<CTree<T>::node<T>>(val);
		return node.second->l;
	}
	
	node.second->r = std::make_shared<CTree<T>::node<T>>(val);
	return node.second->r;
}

template<typename T>
inline std::shared_ptr<CTree<T>::node<T>> CTree<T>::add_val(const T val, std::shared_ptr<CTree<T>::node<T>> dest, bool left)
{
	if (!root)
	{
		root = std::make_shared<CTree<T>::node<T>>(val);
		return root;
	}

	if (left)
	{
		dest->l = std::make_shared<node<T>>(val);
		return dest->l;
	}
	
	dest->r = std::make_shared<node<T>>(val);
	return dest->r;
}

template<typename T>
inline const std::shared_ptr<CTree<T>::node<T>> CTree<T>::find_node(const T val, const std::shared_ptr<CTree<T>::node<T>> start_node) const
{
	if (!root)
		return nullptr;

	auto cur_node = start_node;

	if (!cur_node)
		cur_node = root;

	if (cur_node->item == val)
		return cur_node;
	else
	{
		if (cur_node->l)
		{
			auto node = find_node(val, cur_node->l);
			if (node)
				return node;
		}
		
		if (cur_node->r)
		{
			auto node = find_node(val, cur_node->r);
			if (node)
				return node;
		}
	}

	return nullptr;
}

template<typename T>
inline std::shared_ptr<CTree<T>::node<T>> CTree<T>::get_rand_node()
{
	size_t h = rand() % num_nodes(root);
	size_t cur = 0;

	std::stack<decltype(root)> s;

	s.push(root);

	while (!s.empty())
	{
		auto node = s.top();
		s.pop();

		if (cur != h)
			++cur;
		else
			return node;

		if (node->r)
			s.push(node->r);
		if (node->l)
			s.push(node->l);
	}

	return nullptr;
}

template<typename T>
inline std::pair<size_t, std::shared_ptr<CTree<T>::node<T>>> CTree<T>::get_shortest_node(std::shared_ptr<node<T>> cur_node)
{
	if (!cur_node)
		return std::make_pair(-1, nullptr);

	if (!cur_node->l || !cur_node->r)
		return std::make_pair(0, cur_node);

	auto p_l = get_shortest_node(cur_node->l);
	auto p_r = get_shortest_node(cur_node->r);

	if (p_l.first > p_r.first)
		return std::make_pair(p_r.first + 1, !p_r.second ? cur_node : p_r.second);
	return std::make_pair(p_l.first + 1, !p_l.second ? cur_node : p_l.second);
}

template<typename T>
void CTree<T>::print_node(T item, size_t offset) const
{
	for (size_t i = 0; i != offset; ++i)
		cout << ' ';
	cout << item;
}

template<typename T>
void CTree<T>::print(std::shared_ptr<node<T>> curr_node, size_t offset, size_t start_offset) const
{
	if (!curr_node)
	{
		print_node('*', start_offset);
		cout << endl;
		return;
	}

	if (!curr_node->l && !curr_node->r)
	{
		print_node(curr_node->item, start_offset);
		print_node('-', 0);
		cout << endl;
	}
	else
	{
		//cout << endl;
		print(curr_node->r, offset, start_offset + offset);
		
		print_node(curr_node->item, start_offset);
		cout << endl;

		print(curr_node->l, offset, start_offset + offset);
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
std::shared_ptr<CTree<T>::node<T>> max(const std::vector<T>& mas, size_t l, size_t r)
{
	if (r < l)
		return nullptr;

	size_t m = (l + r) / 2;

	auto x = std::make_shared<CTree<T>::node<T>>(mas[m]);

	if (l == r)
		return x;

	x->l = max(mas, l, m);
	x->r = max(mas, m + 1, r);

	T u = x->l->item, v = x->r->item;

	if (u > v)
		x->item = u;
	else
		x->item = v;

	return x;
}

template<typename T>
CTree<T> generate_tree_max(const std::vector<T>& mas)
{
	auto node = max<T>(mas, 0, mas.size() - 1);

	return CTree<T>(node);
}

template<typename T>
CTree<T> generate_tree_random(const size_t size, const T first_val, const T rand_max)
{
	auto tree = CTree<T>(first_val + rand() % rand_max, 1);

	for (size_t i = 0; i < size - 1; ++i)
	{
		auto node = tree.get_rand_node();

		if(!node || node->l && node->r)
			tree.add_val(first_val + rand() % rand_max);
		else
		{
			if (!node->l && !node->r)
				tree.add_val(first_val + rand() % rand_max, node, rand() % 2);
			else if (node->l)
				tree.add_val(first_val + rand() % rand_max, node, false);
			else
				tree.add_val(first_val + rand() % rand_max, node, true);
		}
	}

	return tree;
}

#endif
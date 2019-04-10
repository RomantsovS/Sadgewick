#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <memory>

using std::cout;
using std::cin;
using std::endl;

template<typename T>
struct node
{
	node() : next(nullptr) {}
	node(T x, node *t = nullptr) : item(x), next(t) {}

	T item;
	node *next;
};

template <typename T>
using link = node<T> *;

template <typename T>
link<T> freelist = nullptr;

template <typename T>
void construct(int N)
{
	freelist = new node<T>[N + 1];

	for (size_t i = 0; i != N; ++i)
	{
		freelist[i].next = &freelist[i + 1];
	}
}

template <typename T>
void destruct()
{
	delete[] freelist;
}

template <typename T>
void insert(link<T> x, link<T> t)
{
	t->next = x->next;
	x->next = t;
}

template <typename T>
link<T> remove(link<T> x)
{
	link t = x->next;
	x->next = t->next;
	return t;
}

template <typename T>
link<T> newNode(int i)
{
	link<T> x = remove(freelist<T>);
	x->item = i;
	x->next = x;
	      
	return x;
}

template <typename T>
void deleteNode(link<T> x)
{
	insert(freelist<T>, x);
}


template <typename T>
link<T> newNodeN(T i)
{
	auto t = new node<T>(i);

	//cout << "new " << t << endl;

	return t;
}


template <typename T>
void deleteNodeN(link<T> x)
{
	//cout << "del " << x << endl;
	delete x;
}


template <typename T>
link<T> next(link<T> x)
{
	return x->next;
}

template <typename T>
int item(link<T> x)
{
	return x->item;
}


template <typename T>
void printList(link<T> t)
{
	if (!t)
	{
		cout << "Empty link\n";
		return;
	}

	auto x = t;

	do
	{
		cout << x->item << endl;

		x = x->next;
	} while (x != t && x);
}


template <typename T>
link<T> generateList(size_t len, T start)
{
	auto t = newNodeN(start);

	auto x = t;

	for (size_t i = 1; i < len; ++i)
	{
		x = (x->next = newNodeN(start + i));
	}

	return t;
}


template <typename T>
link<T> generateRandList(size_t len, size_t max_val)
{
	link t = new node(rand() % max_val, 0);

	link x = t;

	for (size_t i = 1; i < len; ++i)
	{
		x = (x->next = new node(rand() % max_val, 0));
	}

	return t;
}


template <typename T>
link<T> generateCircularList(size_t len, int start)
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


template <typename T>
void inverse_list(link<T> &x)
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

template <typename T>
void sort_list(link<T> &a)
{
	auto b = new node(0), x, u, t;

	for (t = a->next; t != 0; t = u)
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

#endif
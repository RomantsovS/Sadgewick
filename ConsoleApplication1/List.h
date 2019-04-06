#ifndef LIST_H
#define LIST_H

#include <iostream>

using std::cout;
using std::cin;
using std::endl;

struct node
{
	node() : next(nullptr) {}
	node(int x, node *t = nullptr) : item(x), next(t) {}

	int item;
	node *next;
};

using link = node *;

link freelist = nullptr;

void construct(int N)
{
	freelist = new node[N + 1];

	for (size_t i = 0; i != N; ++i)
	{
		freelist[i].next = &freelist[i + 1];
	}
}

void destruct()
{
	delete[] freelist;
}

void insert(link x, link t)
{
	t->next = x->next;
	x->next = t;
}

link remove(link x)
{
	link t = x->next;
	x->next = t->next;
	return t;
}

link newNode(int i)
{
	link x = remove(freelist);
	x->item = i;
	x->next = x;
	      
	return x;
}

void deleteNode(link x)
{
	insert(freelist, x);
}

link newNodeN(int i)
{
	link t = new node(i);

	//cout << "new " << t << endl;

	return t;
}

void deleteNodeN(link x)
{
	//cout << "del " << x << endl;
	delete x;
}

link next(link x)
{
	return x->next;
}

int item(link x)
{
	return x->item;
}

void printList(link t)
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

link generateList(size_t len, int start)
{
	auto t = newNodeN(start);

	auto x = t;

	for (size_t i = 1; i < len; ++i)
	{
		x = (x->next = newNodeN(start + i));
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
	link b = new node(0), x, u, t;

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
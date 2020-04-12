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
		freelist[i].next = &freelist<T>[i + 1];
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
	auto t = newNodeN<T>(start);

	auto x = t;

	for (size_t i = 1; i < len; ++i)
	{
		x = (x->next = newNodeN<T>(start + i));
	}

	return t;
}


template <typename T>
link<T> generateRandList(size_t len, size_t max_val)
{
	auto t = new node<T>(rand() % max_val, 0);

	auto x = t;

	for (size_t i = 1; i < len; ++i)
	{
		x = (x->next = new node<T>(rand() % max_val, 0));
	}

	return t;
}


template <typename T>
link<T> generateCircularList(size_t len, int start)
{
	auto t = new node<T>(start, 0);

	auto x = t;

	for (size_t i = 1; i < len; ++i)
	{
		x = (x->next = new node<T>(start + i));
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

template<typename T> class CList;

template<typename T>
class CList
{
public:
	template<typename T>
	struct node
	{
		node() : next(nullptr) {}
		node(T x, std::shared_ptr<node> t = nullptr) : item(x), next(t) {}

		T item;
		std::shared_ptr<node> next;
	};

	CList() : head(nullptr), curr(head) {}

	std::shared_ptr<node<T>> &get_head()
	{
		return head;
	}

	void insert(std::shared_ptr<node<T>> x, std::shared_ptr<node<T>> t);
	void emplace(T val, std::shared_ptr<node<T>> t = nullptr);

	void remove(std::shared_ptr<node<T>> x);

	bool empty();
	std::shared_ptr<node<T>> next(std::shared_ptr<node<T>> t)
	{
		return t->next;
	}

	void print(std::shared_ptr<node<T>> curr_ptr = nullptr);
private:
	std::shared_ptr<node<T>> head;
	std::shared_ptr<node<T>> curr;
};

template<typename T>
inline void CList<T>::insert(std::shared_ptr<node<T>> dest, std::shared_ptr<node<T>> ptr)
{
	ptr->next = dest->next;
	dest->next = ptr;
}

template<typename T>
inline void CList<T>::emplace(T val, std::shared_ptr<node<T>> t)
{
	if (!t)
		t = curr;

	auto ptr = std::make_shared<node<T>>(val);

	if (empty())
		ptr->next = curr = head = ptr;
	else
	{
		ptr->next = curr->next;
		curr->next = ptr;
		curr = ptr;
	}
}

template<typename T>
inline void CList<T>::remove(std::shared_ptr<node<T>> x)
{
	auto t = x->next;

	if (x->next == head)
		head = t->next;

	x->next = t->next;
}

template<typename T>
inline bool CList<T>::empty()
{
	return !head;
}

template<typename T>
inline void CList<T>::print(std::shared_ptr<node<T>> curr_ptr)
{
	if (empty())
		cout << "list is empty\n";

	if (!curr_ptr)
		curr_ptr = head;

	auto start = curr_ptr;

	do
	{
		cout << curr_ptr->item << " ";
		curr_ptr = curr_ptr->next;
	} while (curr_ptr != start);

	cout << endl;
}

#endif
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../List.h"

constexpr size_t N = 10;

template <typename T>
link<T> merge(link<T> a, link<T> b)
{ 
	node<T> dummy(0);
	link<T> head = &dummy, c = head;
	while ((a != 0) && (b != 0))
		if (a->item < b->item)
		{
			c->next = a;
			c = a;
			a = a->next;
		}
		else
		{
			c->next = b;
			c = b;
			b = b->next;
		}
	c->next = (a == 0) ? b : a;
	return head->next;
}

template <typename T>
link<T> mergesort(link<T> c)
{
	if (c == 0 || c->next == 0)
		return c;
	link<T> a = c, b = c->next;
	while ((b != 0) && (b->next != 0))
	{
		c = c->next;
		b = b->next->next;
	}
	b = c->next;
	c->next = 0;
	return merge(mergesort(a), mergesort(b));
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		std::cout << "cnt = " << i << std::endl;

		auto head = generateRandList(10, 'A', 'M');

		printList(head);

		head = mergesort(head);

		printList(head);
		
	}

	return 0;
}
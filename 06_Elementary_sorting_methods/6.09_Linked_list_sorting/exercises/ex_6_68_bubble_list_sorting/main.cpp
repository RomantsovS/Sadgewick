#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../List.h"

template <typename T>
void bubble_list_sort(link<T> &h)
{
	link<T> out = h;
	link<T> last = nullptr;

	for (auto t = out; t != nullptr; t = t->next)
	{
		link<T> prev = nullptr;
		auto u = out;

		while (u->next && u->next != last)
		{
			if (u->item > u->next->item)
			{
				auto next_next = u->next->next;
				u->next->next = u;

				if (!prev)
				{
					out = u->next;
				}
				else
				{
					prev->next = u->next;
				}

				prev = u->next;
				u->next = next_next;
			}
			else
			{
				prev = u;
				u = u->next;
			}
		}
		last = u;
	}

	h = out;
}

int main()
{
	for (size_t i = 1; i <= 100000; i *= 10)
	{
		cout << "cnt = " << i << endl;
		link<int> lst;
		srand(clock());
		lst = generateRandList<int>(i, 0, 10);

		//printList(lst);

		auto t = clock();
		bubble_list_sort(lst);
		std::cout << (clock() - t) << endl;
		//printList(lst);

		delete_list(lst);
	}

	return 0;
}
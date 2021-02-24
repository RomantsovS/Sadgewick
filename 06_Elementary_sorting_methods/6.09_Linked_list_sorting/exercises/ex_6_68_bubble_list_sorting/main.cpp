#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <stack>

#include "../../../../List.h"

template <typename T>
void bubble_list_sort(link<T>& h) {
	link<T> out = h;

	for (auto t = out; t != nullptr; t = t->next)
	{
		std::stack<link<T>> st;
		for (auto u = out; u != nullptr; u = u->next) {
			st.push(u);
		}

		while (!st.empty()) {
			auto last = st.top();
			st.pop();

			if (st.empty()) {
				break;
			}

			auto pre_last = st.top();
			st.pop();

			if(last->item < pre_last->item) {
				auto last_next = last->next;
				last->next = pre_last;
				pre_last->next = last_next;

				if(st.empty()) {
					out = last;
					break;
				}
				else {
					auto pre_pre = st.top();
					pre_pre->next = last;
				}
				st.push(last);
			}
			else {
				st.push(pre_last);
			}
		}
	}

	h = out;
}

int main()
{
	link<int> lst;
	lst = generateRandList<int>(20, 0, 10);

	printList(lst);

	bubble_list_sort(lst);

	printList(lst);

	delete_list(lst);

	return 0;
}
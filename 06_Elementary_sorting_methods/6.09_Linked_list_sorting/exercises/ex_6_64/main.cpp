#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../List.h"

template<typename T>
link<T> findmax(link<T> h) {
	link<T> prev_max_node = h;
	T max = h->item;

	while(h->next) {
		if(h->next->item > max) {
			prev_max_node = h;
			max = h->next->item;
		}
		h = h->next;
	}

	return prev_max_node;
}

template<typename T>
link<T> list_selection_sort(link<T> h) {
	node<T> dummy{0};
	link<T> head = &dummy, out = nullptr;

	head->next = h;

	while(head->next != nullptr) {
		link<T> max = findmax(head), t = max->next;

		max->next = t->next;
		t->next = out;
		out = t;
	}

	return out;
}

int main() {
	link<char> lst = new node<char>{'A'};
	lst->next = new node<char>{'S'};
	lst->next->next = new node<char>{'O'};
	lst->next->next->next = new node<char>{'R'};
	lst->next->next->next->next = new node<char>{'T'};
	lst->next->next->next->next->next = new node<char>{'I'};

	printList(lst);

	auto out = list_selection_sort(lst);

	printList(out);

	printList(lst);

	delete_list(out);

	return 0;
}
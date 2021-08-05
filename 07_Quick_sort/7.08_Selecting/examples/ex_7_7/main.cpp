#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <stack>

#include "../../../../Mas.h"
#include "../../../../Sort/sort.h"

int M = 10, mas_size = 100, max_elem = 10;

template <typename Item>
int partition(Item a[], int l, int r)
{
	int i = l - 1, j = r, v = a[r];

	for (;;)
	{
		while (a[++i] < v)
			;
		while (v < a[--j])
			if (j == l)
				break;
		if (i >= j)
			break;

		std::swap(a[i], a[j]);
	}

	std::swap(a[i], a[r]);
	
	return i;
}

template <typename Item>
void select(Item a[], int l, int r, int k)
{
	while (r > l)
	{
		int i = partition(a, 1, r);
		if (i >= k)
			r = i - 1;
		if (i <= k)
			l = i + 1;
	}
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		char mas[] = {'a', 's', 'o', 'r', 't', 'i', 'n', 'g',
		'e', 'x', 'a', 'm', 'p', 'l', 'e'};

		mas_size = sizeof(mas) / sizeof(char);

		print_mas(mas, mas + mas_size);

		auto start_time = clock();

		select(mas, 0, mas_size - 1, mas_size / 2);

		print_mas(mas, mas + mas_size);

		std::cout << (clock() - start_time) << endl;
	}

	return 0;
}
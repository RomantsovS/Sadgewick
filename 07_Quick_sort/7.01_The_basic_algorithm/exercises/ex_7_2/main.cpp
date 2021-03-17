#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../Mas.h"

constexpr size_t M = 10, maxN = 10;

template <typename Item>
int partition(std::vector<Item> &a, int l, int r)
{
	int i = l - 1, j = r, v = a[r];

	for (;;)
	{
		while (a[++i] < v)
			;
		while (v < a[--j])
			if (j == 1)
				break;
		if (i >= j)
			break;

		std::swap(a[i], a[j]);
	}

	std::swap(a[i], a[r]);
	
	return i;
}

template <typename Item>
void quicksort(std::vector<Item> &a, int l, int r)
{
	if (r <= l)
		return;

	int i = partition(a, l, r);

	quicksort(a, l, i - 1);
	quicksort(a, i + 1, r);
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		std::cout << "cnt = " << i << std::endl;

		std::vector<int> mas{1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0};

		print_mas(mas, 3);

		quicksort(mas, 0, mas.size() - 1);

		print_mas(mas, 3);
	}

	return 0;
}
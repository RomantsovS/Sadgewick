#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <stack>

#include "../../../../Mas.h"
#include "../../../../Sort/sort.h"

int M = 10, mas_size = 100, max_elem = 10;

template <typename Item>
int partition(std::vector<Item> &a, int l, int r)
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
void quicksort(std::vector<Item> &a, int l, int r)
{
	if(r - l <= M)
		return;

	std::swap(a[(l + r) / 2], a[r-1]);
	compexch(a[l], a[r-1]);
	compexch(a[l], a[r]);
	compexch(a[r-1], a[r]);

	int i = partition(a, l + 1, r - 1);
	quicksort(a, l, i - 1);
	quicksort(a, i + 1, r);
}

template <typename Item>
void hybridsort(std::vector<Item> &a, int l, int r)
{
	quicksort(a, l, r);
	insertion_sort(a, 0, l, r);
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		std::vector<int> mas(mas_size);

		for (size_t j = 0; j < mas.size(); ++j)
		{
			mas[j] = rand() % (max_elem);
		}

		print_mas(mas, 3);

		auto start_time = clock();

		hybridsort(mas, 0, mas.size() - 1);

		print_mas(mas, 3);

		std::cout << (clock() - start_time) << endl;
	}

	return 0;
}
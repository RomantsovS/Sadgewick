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
	int k;
	Item v = a[r];

	if(r <= l) return;

	int i = l - 1, j = r, p = l - 1, q = r;

	for(;;) {
		while(a[++i] < v) ;
		while(v < a[--j]) if(j == l) break;
		if(i >= j) break;
		std::swap(a[i], a[j]);
		if(a[i] == v) { p++; std::swap(a[p], a[i]); }
		if(v == a[j]) { q--; std::swap(a[q], a[j]); }
	}

	std::swap(a[i], a[r]); j = i - 1; i = i + 1;
	for(k = l; k <= p; k++, j--) std::swap(a[k], a[j]);
	for(k = r - 1; k >= q; k--, i++) std::swap(a[k], a[i]);

	quicksort(a, l, j);
	quicksort(a, i, r);
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

		quicksort(mas, 0, mas.size() - 1);

		print_mas(mas, 3);

		std::cout << (clock() - start_time) << endl;
	}

	return 0;
}
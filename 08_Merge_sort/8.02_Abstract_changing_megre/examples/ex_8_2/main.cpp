#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../Mas.h"
#include "../../../../Sort/sort.h"

constexpr size_t M = 10, maxN = 10;

template <class Item>
void merge(Item a[], int l, int m, int r)
{
	int i, j;
	static Item aux[maxN];
	for (i = m + 1; i > l; i--)
		aux[i - 1] = a[i - 1];
	for (j = m; j < r; j++)
		aux[r + m - j] = a[j + 1];
	for (int k = l; k <= r; k++)
		if (aux[j] < aux[i])
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		std::cout << "cnt = " << i << std::endl;
		std::vector<char> mas1{'A', 'R', 'S', 'T', 'G', 'I', 'N'};

		print_mas(mas1, 3);

		merge(&mas1.front(), 0, mas1.size() / 2, mas1.size() - 1);

		print_mas(mas1, 3);
	}

	return 0;
}
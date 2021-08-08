#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../Mas.h"
#include "../../../../Sort/sort.h"

constexpr size_t maxN = 10;

template <class Item>
void mergeAB(Item c[], Item a[], int N,
			 Item b[], int M)
{
	for (int i = 0, j = 0, k = 0; k < N + M; k++)
	{
		if (i == N)
		{
			c[k] = b[j++];
			continue;
		}
		if (j == M)
		{
			c[k] = a[i++];
			continue;
		}
		c[k] = (a[i] < b[j]) ? a[i++] : b[j++];
	}
}

template <class Item>
void mergesortABr(Item a[], Item b[], int l, int r)
{
	if (r - l <= 10)
	{
		insertion_sort(a, l, r);
		return;
	}
	int m = (l + r) / 2;
	mergesortABr(b, a, l, m);
	mergesortABr(b, a, m + 1, r);
	mergeAB(a + l, b + l, m - l + 1, b + m + 1, r - m);
}

template <class Item>
void mergesortAB(Item a[], int l, int r)
{
	static Item aux[maxN];
	for (int i = l; i <= r; i++)
		aux[i] = a[i];
	mergesortABr(a, aux, l, r);
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		std::cout << "cnt = " << i << std::endl;
		std::vector<char> mas1{'A', 'R', 'S', 'T', 'G', 'I', 'N'};

		print_mas(mas1, 3);

		mergesortAB(&mas1.front(), 0, mas1.size() - 1);

		print_mas(mas1, 3);
	}

	return 0;
}
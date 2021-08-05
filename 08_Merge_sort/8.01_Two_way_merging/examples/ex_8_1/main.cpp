#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../Mas.h"
#include "../../../../Sort/sort.h"

constexpr size_t M = 10, maxN = 10;

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

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		std::cout << "cnt = " << i << std::endl;
		std::vector<int> mas1(maxN), mas2(maxN), mas3(maxN * 2);

		for (size_t j = 0; j < maxN; ++j)
		{
			mas1[j] = rand() % (M - 1);
			mas2[j] = rand() % (M - 1);
		}

		print_mas(mas1, 3);
		print_mas(mas2, 3);

		quicksort(mas1, 0, mas1.size() - 1);
		quicksort(mas2, 0, mas2.size() - 1);

		print_mas(mas1, 3);
		print_mas(mas2, 3);

		mergeAB(&mas3.front(), &mas1.front(), mas1.size(), &mas2.front(),
		mas2.size());

		print_mas(mas3, 3);
	}

	return 0;
}
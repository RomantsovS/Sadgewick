#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../Mas.h"
#include "../../../../Sort/sort.h"

constexpr size_t N = 10;

inline int min(int A, int B)
{
	return (A < B) ? A : B;
}

template <class Item>
void mergesortBU(Item a[], int l, int r)
{
	for (int m = 1; m <= r - l; m = m + m)
		for (int i = l; i <= r - m; i += m + m)
			merge(a, i, i + m - 1, min(i + m + m - 1, r));
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		std::cout << "cnt = " << i << std::endl;
		std::vector<char> mas1{'A', 'S', 'O', 'R', 'T', 'I', 'N', 'G', 'E', 'X', 'A',
		'M', 'P', 'L', 'E'};

		print_mas(mas1, 3);

		mergesortBU(&mas1.front(), 0, mas1.size() - 1);

		print_mas(mas1, 3);
	}

	return 0;
}
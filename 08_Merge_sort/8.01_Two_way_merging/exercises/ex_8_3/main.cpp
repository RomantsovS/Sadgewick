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
		std::vector<char> mas1 {'A', 'E', 'Q', 'S', 'U', 'Y', 'E', 'I', 'N',
		'O', 'S', 'T'};

		print_mas(mas1, 3);

		mergeAB(&mas1.front(), &mas1.front(), mas1.size() / 2,
		&mas1.front() + mas1.size() / 2, mas1.size() - mas1.size() / 2);

		print_mas(mas1, 3);
	}

	return 0;
}
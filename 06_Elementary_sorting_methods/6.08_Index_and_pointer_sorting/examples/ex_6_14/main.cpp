#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../Sort/sort.h"

struct intWrapper {
	int item;
	intWrapper(int i = 0)
	{
		item = i;
	}
	operator int() const
	{
		return item;
	}
};

template <typename Item>
void insitu(Item data[], intWrapper a[], size_t N)
{
	for (int i = 0; i < N; i++)
	{
		Item v = data[i];
		int j, k;

		for (k = i; a[k] != i; k = a[j], a[j] = j)
		{
			j = k;
			data[k] = data[a[k]];
		}
		data[k] = v;
		a[k] = k;
	}
}

int main()
{
	size_t N = 10;

	std::default_random_engine rand_eng;
	std::uniform_int_distribution<int> u_ch(0, 9);

	vector<int> mas;

	for (size_t i = 0; i != N; ++i)
	{
		mas.push_back(u_ch(rand_eng));
	}

	print_mas(mas);

	vector<intWrapper> a({2, 4, 6, 8, 0, 1, 3, 5, 7, 9});

	insitu(&mas.front(), &a.front(), N);

	print_mas(mas);

	return 0;
}
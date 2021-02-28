#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../Mas.h"

constexpr size_t M = 10, maxN = 10;

void distcount(int a[], size_t l, size_t r) {
	size_t i, j, cnt[M];
	static int b[maxN];

	for(j = 0; j < M; ++j) 
		cnt[j] = 0;
	for(i = l; i <= r; ++i)
		cnt[a[i] + 1]++;
	for(j = 1; j < M; ++j)
		cnt[j] += cnt[j - 1];
	for(i = l; i <= r; ++i)
		b[cnt[a[i]]++] = a[i];
	for(i = l; i <= r; ++i)
		a[i] = b[i - 1];
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		std::cout << "cnt = " << i << std::endl;
		std::vector<int> mas(maxN);

		for(size_t j = 0; j < maxN; ++j) {
			mas[j] = rand() % (M - 1);
		}

		print_mas(mas, 3);

		distcount(&mas[0], 0, maxN - 1);

		print_mas(mas, 3);
	}

	return 0;
}
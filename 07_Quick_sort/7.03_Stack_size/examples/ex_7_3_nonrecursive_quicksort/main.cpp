#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <stack>

#include "../../../../Mas.h"

constexpr size_t M = 10, maxN = 10;

inline void push2(std::stack<int> &s, int A, int B) {
	s.push(B);
	s.push(A);
}

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
	std::stack<int > s;
	push2(s, l, r);

	while(!s.empty()) {
		l = s.top();
		s.pop();
		r = s.top();
		s.pop();

		if(r <= l ) continue;

		int i = partition(a, l, r);

		if (i - 1 > r - i) {
			push2(s, l, i - 1);
			push2(s, i + 1, r);
		}
		else {
			push2(s, i + 1, r);
			push2(s, l, i - 1);
		}
	}
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		std::cout << "cnt = " << i << std::endl;
		std::vector<int> mas(maxN);

		for (size_t j = 0; j < maxN; ++j)
		{
			mas[j] = rand() % (M - 1);
		}

		mas.push_back(-1);

		print_mas(mas, 3);

		quicksort(mas, 0, mas.size() - 1);

		print_mas(mas, 3);
	}

	return 0;
}
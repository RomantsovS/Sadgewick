#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <stack>

#include "../../../../Mas.h"
#include "../../../../Sort/sort.h"

size_t M = 10, maxN = 100;

int max_elem = 5;

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

		if(r <= l) continue;

		if(r - l <= max_elem) continue;

		int i = partition(a, l, r);

		if (i - l > r - i) {
			push2(s, l, i - 1);
			push2(s, i + 1, r);
		}
		else {
			push2(s, i + 1, r);
			push2(s, l, i - 1);
		}
	}

	insertion_sort(a, 0, l, r);
}

int f() {
	std::vector<int> mas(maxN);

	for (size_t j = 0; j < maxN; ++j)
	{
		mas[j] = rand() % (M - 1);
	}

	auto start_time = clock();
	
	quicksort(mas, 0, mas.size() - 1);
	
	return clock() - start_time;
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		int t;

		max_elem = 10;
		maxN = 1000;
		t = f();
		std::cout << "MaxN: " << maxN << " max_elem: " << max_elem << " : "
		<< t << endl;

		max_elem = 100;
		maxN = 1000;
		t = f();
		std::cout << "MaxN: " << maxN << " max_elem: " << max_elem << " : "
		<< t << endl;

		max_elem = 1000;
		maxN = 1000;
		t = f();
		std::cout << "MaxN: " << maxN << " max_elem: " << max_elem << " : "
		<< t << endl;

		max_elem = 10;
		maxN = 10000;
		t = f();
		std::cout << "MaxN: " << maxN << " max_elem: " << max_elem << " : "
		<< t << endl;

		max_elem = 100;
		maxN = 10000;
		t = f();
		std::cout << "MaxN: " << maxN << " max_elem: " << max_elem << " : "
		<< t << endl;

		max_elem = 1000;
		maxN = 10000;
		t = f();
		std::cout << "MaxN: " << maxN << " max_elem: " << max_elem << " : "
		<< t << endl;

		max_elem = 10;
		maxN = 100000;
		t = f();
		std::cout << "MaxN: " << maxN << " max_elem: " << max_elem << " : "
		<< t << endl;

		max_elem = 100;
		maxN = 100000;
		t = f();
		std::cout << "MaxN: " << maxN << " max_elem: " << max_elem << " : "
		<< t << endl;

		max_elem = 1000;
		maxN = 100000;
		t = f();
		std::cout << "MaxN: " << maxN << " max_elem: " << max_elem << " : "
		<< t << endl;
	}

	return 0;
}
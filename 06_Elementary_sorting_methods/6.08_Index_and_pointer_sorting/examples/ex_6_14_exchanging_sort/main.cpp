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
	std::string str{"a s o r t i n g e x a m p l e"};
	std::istringstream is{str};

	vector<char> mas;

	char ch;
	while(is >> ch) {
		mas.push_back(ch);
	}

	print_mas(mas);

	vector<intWrapper> a({0, 10, 8, 14, 7, 5, 13, 11, 6, 2, 12, 3, 1, 4, 9});

	insitu(&mas.front(), &a.front(), mas.size());

	print_mas(mas);

	return 0;
}
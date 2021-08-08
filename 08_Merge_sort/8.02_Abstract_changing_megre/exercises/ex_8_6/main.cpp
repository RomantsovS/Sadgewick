#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../Mas.h"
#include "../../../../Sort/sort.h"

constexpr size_t maxN = 15;

struct Str{
	Str(const char* _str = "")
	{
		str = new char[strlen(_str) + 1];
		strcpy(str, _str);
	}

	bool operator<(const Str& r)
	{
		return str[0] < r.str[0];
	}

	bool operator==(const Str& r)
	{
		return str[0] == r.str[0];
	}

	char* str;
};

std::ostream& operator<<(std::ostream& os, const Str& str)
	{
		os << str.str;
		return os;
	}

template <class Item>
void merge(Item a[], int l, int m, int r)
{
	int i, j;
	static Item aux[maxN];
	for (i = m + 1; i > l; i--)
		aux[i - 1] = a[i - 1];
	for (j = m; j < r; j++) {
		aux[r + m - j] = a[j + 1];
	}
	print_mas(aux, aux + r + 1, 3);

	for (int k = l; k <= r; k++)
		if (aux[j] < aux[i])
			a[k] = aux[j--];
		else if(i > m && aux[i] == aux[j])
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
}

int main()
{
	for (size_t i = 1; i <= 1; i++)
	{
		std::cout << "cnt = " << i << std::endl;
		std::vector<Str> mas1;
		/*mas1.push_back("AA");
		mas1.push_back("BB");
		mas1.push_back("CD");
		mas1.push_back("CC");
		mas1.push_back("CE");*/

		srand(time(0));

		for (int i = 0; i < 15; ++i)
		{
			char str[3];
			str[0] = {static_cast<char>('A' + rand() % 5)};
			str[1] = {static_cast<char>('A' + rand() % 5)};
			str[2] = 0;
			mas1.push_back(Str(str));
		}

		print_mas(mas1, 3);
		quicksort(mas1, 0, mas1.size() / 2, 0);
		quicksort(mas1, mas1.size() / 2 + 1, mas1.size() - 1, 0);

		print_mas(mas1, 3);

		merge(&mas1.front(), 0, mas1.size() / 2, mas1.size() - 1);

		print_mas(mas1, 3);
	}

	return 0;
}
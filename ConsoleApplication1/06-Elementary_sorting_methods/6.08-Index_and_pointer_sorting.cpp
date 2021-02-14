#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <iomanip>

#include "../Mas.h"
#include "../Complex.h"
#include "../Sort.h"

struct Item {
	char* str;
};

static char buf[10000];
static size_t cnt = 0;

bool operator< (const Item& a, const Item& b)
{
	return strcmp(a.str, b.str) < 0;
}

bool operator> (const Item& a, const Item& b)
{
	return strcmp(a.str, b.str) > 0;
}

void show(const Item& x)
{
	cout << x.str << " ";
}

bool scan(Item& x)
{
	bool flag = !!(cin >> (x.str = &buf[cnt]));
	cnt += strlen(x.str) + 1;
	return flag;
}

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

void ex_6_11()
{
	vector<Item> ivec;

	for (Item i; scan(i);)
	{
		ivec.push_back(i);
	}

	insertion_sort(ivec);

	for (const auto& item : ivec)
	{
		show(item);
		cout << endl;
	}

	cout << endl;
}

struct record {
	char name[30];
	int num;
};

struct recordItem{
	record* r;
};

bool operator<(const recordItem& a, const recordItem& b)
{
	return a.r->num < b.r->num;
}

bool operator>(const recordItem& a, const recordItem& b)
{
	return a.r->num > b.r->num;
}

static record data[50];

void show(const recordItem& x)
{
	cout << x.r->name << " " << x.r->name << endl;
}

bool scan(recordItem& x)
{
	x.r = &data[cnt++];
	return !!(cin >> x.r->name >> x.r->name);
}

void ex_6_13()
{
	vector<recordItem> ivec;

	for (recordItem i; scan(i);)
	{
		ivec.push_back(i);
	}

	insertion_sort(ivec);

	for (const auto& item : ivec)
	{
		show(item);
		cout << endl;
	}

	cout << endl;
}

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

void ex_6_14()
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
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_6_14();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
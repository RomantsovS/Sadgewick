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

struct record {
	char name[30];
	int num;
};

struct Item{
	record* r;
};

bool operator<(const Item& a, const Item& b)
{
	return a.r->num < b.r->num;
}

bool operator>(const Item& a, const Item& b)
{
	return a.r->num > b.r->num;
}

static size_t cnt = 0;
static record data[50];

void show(const Item& x)
{
	cout << x.r->name << " " << x.r->num << endl;
}

bool scan(Item& x)
{
	x.r = &data[cnt++];
	return !!(cin >> x.r->name >> x.r->num);
}

int main()
{
	vector<Item> ivec;

	for (Item i; scan(i);)
	{
		ivec.push_back(i);
	}

	insertion_sort(ivec, 0);

	for (const auto& item : ivec)
	{
		show(item);
		cout << endl;
	}

	cout << endl;

	return 0;
}
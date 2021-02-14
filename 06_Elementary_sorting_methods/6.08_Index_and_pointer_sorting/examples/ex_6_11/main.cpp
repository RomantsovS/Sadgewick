#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../Sort/sort.h"

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
/*
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

using Index = intWrapper;

bool operator< (const Index &i, const Index& j) {
	return data[i] < data[j];
}
*/
int main()
{
	vector<Item> ivec;

	for (Item i; scan(i);) {
		ivec.push_back(i);
	}

	insertion_sort(ivec, 100);

	for (const auto& item : ivec) {
		show(item);
		cout << endl;
	}

	cout << endl;

	return 0;
}
#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

#include "../../../../Sort/sort.h"

struct record {
	char name[30];
	int num;
};

bool operator<(const record& a, const record& b)
{
	return a.num < b.num;
}

bool operator>(const record& a, const record& b)
{
	return a.num > b.num;
}

static size_t cnt = 0;
static record data[50];

void show(const record& x)
{
	cout << x.name << " " << x.num << endl;
}

bool scan(record& x)
{
	return !!(cin >> x.name >> x.num);
}

int main()
{
	vector<record> ivec;

	for (record i; scan(i);)
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
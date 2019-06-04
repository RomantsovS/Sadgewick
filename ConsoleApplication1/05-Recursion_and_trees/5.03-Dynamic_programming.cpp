#include <iostream>
#include <list>
#include <string>
#include <forward_list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <tuple>
#include <regex>
#include <random>
#include <conio.h>
#include <valarray>
#include <typeinfo>
#include <cctype>
#include <array>
#include <numeric>
#include <math.h>
#include <iomanip>

#include "../Point.h"
#include "../List.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

int64_t f_5_37(size_t j)
{
	int64_t F[2] = { 0, 1 };

	if (j < 2)
		return F[j];

	size_t offset = 0;
	int64_t res = 0;

	for (size_t i = 2; i <= j; ++i)
	{
		res = F[i - 1 - offset] + F[i - 2 - offset];

		F[i - 2 - offset] = F[i - 1 - offset];
		F[i - 1 - offset] = res;

		++offset;
	}

	return res;
}

void ex_5_37()
{
	for(size_t i = 0; i != 100; ++i)
		cout << i << " " << f_5_37(i) << endl;
}

size_t f_5_40(size_t i)
{
	static size_t known[1024];

	if (known[i] != 0)
		return known[i];

	size_t t = i;

	if (i < 1)
		return 0;
	else
		t = static_cast<size_t>(std::floor(i / 2)) + f_5_40(static_cast<size_t>(std::floor(i / 2)))
		+ f_5_40(static_cast<size_t>(std::ceil(i / 2)));

	return known[i] = t;
}

void ex_5_40()
{
	for (size_t i = 0; i != 10; ++i)
		cout << i << " " << f_5_40(i) << endl;
}

size_t f_5_44(size_t i, size_t x)
{
	static size_t known[10];

	size_t t = 0;

	size_t sum = 0;
	
	if (x == 0)
		t = 1;
	else
	{
		for (size_t k = 1; k <= x; ++k)
			sum += known[k - 1] + known[x - k];

		t = x + static_cast<size_t>((1.0 / x) * sum);
	}

	known[x] = t;

	if (i == x)
		return t;
	
	return f_5_44(i, x + 1);
}

void ex_5_44()
{
	for (size_t i = 0; i != 11; ++i)
		cout << i << " " << f_5_44(i, 0) << endl;
}

size_t f_5_45(size_t i)
{
	static size_t known[10];

	if (i == 0)
		return 1;

	if (known[i] != 0)
		return known[i];

	size_t t = 0;

	size_t x = 0;

	for (size_t k = 1; k <= i; ++k)
		x += known[k - 1] + known[i - k];

	t = i + static_cast<size_t>((1.0 / i) * x);

	return known[i] = t;
}

void ex_5_45()
{
	for (size_t i = 0; i != 10; ++i)
		cout << i << " " << f_5_45(i) << endl;
}

struct my_item
{
	size_t size, val;
};

vector<my_item> items = { {3, 4}, {4, 5}, {7, 10}, {8, 11}, {9, 13} };
vector<int> maxknown(18, 0);
vector<my_item> itemsknown(18);

int f_5_48(int M)
{
	int i, space, max, maxi = -1, t;

	if (maxknown[M] != -1)
		return maxknown[M];

	for (i = 0, max = 0; i < static_cast<int>(items.size()); ++i)
	{
		if ((space = M - items[i].size) >= 0)
		{
			if ((t = f_5_48(space) + items[i].val) > max)
			{
				max = t;
				maxi = i;
			}
		}
	}
	
	if (max)
	{
		maxknown[M] = max;
		itemsknown[M] = items[maxi];
	}

	return max;
}

void ex_5_48()
{
	const int bag_size = 17;

	maxknown = vector<int>(18, -1);

	auto max_size = f_5_48(bag_size);
	cout << max_size << endl;

	for (size_t i = 0; i <= bag_size; ++i)
	{
		cout << std::setw(2) << i << " ";
		
		cout << std::setw(2) << maxknown[i] << " ";

		cout << itemsknown[i].size << '-' << itemsknown[i].val << endl;
	}

	cout << endl;

	for (auto i = bag_size; i > 0;)
	{
		cout << itemsknown[i].size << '-' << itemsknown[i].val << endl;
		i -= itemsknown[i].size;
	}
}

void ex_5_51()
{
	const int bag_size = 17;

	size_t max_size = 0;
	int maxi = -1;

	for (size_t i = 0; i <= bag_size; ++i)
	{
		size_t max = 0;

		for(size_t ind = 0; ind != items.size(); ++ ind)
		{
			if (i == items[ind].size)
			{
				if (items[ind].val > max)
				{
					max = items[ind].val;
					maxi = ind;
				}
			}
			else if (i >= items[ind].size)
			{
				for (size_t j = 1; j <= i - items[ind].size; ++j)
				{
					if (items[ind].val + maxknown[j] > max)
					{
						max = items[ind].val + maxknown[j];
						maxi = ind;
					}
				}
			}
		}

		if (max)
		{
			maxknown[i] = max;
			itemsknown[i] = items[maxi];
		}
	}

	cout << max_size << endl;

	for (size_t i = 0; i <= bag_size; ++i)
	{
		cout << std::setw(2) << i << " ";

		cout << std::setw(2) << maxknown[i] << " ";

		cout << itemsknown[i].size << '-' << itemsknown[i].val << endl;
	}

	cout << endl;

	for (auto i = bag_size; i > 0;)
	{
		cout << itemsknown[i].size << '-' << itemsknown[i].val << endl;
		i -= itemsknown[i].size;
	}
}

int f_5_52(int M, int last_item_index)
{
	size_t space, max = 0, t;
	int i, maxi = -1;

	if (maxknown[M] != -1)
		return maxknown[M];

	for (i = last_item_index, max = 0; i >= 0; ++i)
	{
		if ((t = f_5_52(space, last_item_index - 1) + items[i].val) > max)
		{
			max = t;
			maxi = i;
		}
	}

	while(maxknown[M] <= M)
	{
		maxknown[M] += items[last_item_index].size;
		itemsknown[items[last_item_index].size] = items[last_item_index];
	}

	return maxknown[M];
}

void ex_5_52()
{
	const int bag_size = 17;

	maxknown = vector<int>(18, -1);

	auto max_size = f_5_52(bag_size, items.size() - 1);
	cout << max_size << endl;

	for (size_t i = 0; i <= bag_size; ++i)
	{
		cout << std::setw(2) << i << " ";

		cout << std::setw(2) << maxknown[i] << " ";

		cout << itemsknown[i].size << '-' << itemsknown[i].val << endl;
	}

	cout << endl;

	for (auto i = bag_size; i > 0;)
	{
		cout << itemsknown[i].size << '-' << itemsknown[i].val << endl;
		i -= itemsknown[i].size;
	}
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_5_52();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
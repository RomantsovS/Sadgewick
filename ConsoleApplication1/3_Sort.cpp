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
#include <utility>
#include <iomanip>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::list;
using std::forward_list;
using std::map;
using std::set;

constexpr size_t N = 20;
constexpr size_t max_num = 9;

struct data_t
{
	std::vector<int> mas;
	std::function<void(std::vector<int> &, size_t)> func;
	string name;
	size_t speed;
};

void print_mas(const int * beg, const int *end, size_t speed)
{
	static char buffer[(N + 1) * (max_num + 1 + 1)];

	memset(&buffer[0], ' ', (N + 1) * (max_num + 1 + 1));

	static clock_t lastClock = clock();

	system("cls");

	char *p_next_write = &buffer[0];

	auto iter = beg;

	for (int j = max_num; j >= 0; --j)
	{
		iter = beg;
		while(iter < end)
		{
			if (*iter == j)
				*p_next_write = static_cast<char>('0' + j);
			else
				*p_next_write = ' ';

			p_next_write++;
			++iter;
		}

		*p_next_write++ = '\n';
	}

	std::for_each(beg, end, [&p_next_write](auto &val)
	{*p_next_write++ = static_cast<char>('0' + val); });

	std::cout.write(&buffer[0], p_next_write - &buffer[0]);

	cout << endl;

	while (clock() - lastClock < CLOCKS_PER_SEC / 100 * static_cast<int>(speed))
		;
	lastClock = clock();
}

void print_mas(const vector<int> &mas, size_t speed)
{
	print_mas(&mas.front(), &mas.back() + 1, speed);
}

void bubble_sort(std::vector<int> &mas, size_t speed)
{
	bool sorted = false;

	for (size_t i = 0; i != mas.size(); ++i)
	{
		sorted = true;
		for (size_t j = mas.size() - 1; j > i; --j)
		{

			if (mas[j] < mas[j - 1])
			{
				std::swap(mas[j - 1], mas[j]);
				sorted = false;
			}

			print_mas(mas, speed);
		}
		if(sorted)
			break;
	}
}

void shaker_sort(vector<int> &mas, size_t speed)
{
	bool sorted = false;
	bool forward = false;
	
	size_t index = 0;

	for (size_t i = 0; i != mas.size() - 1; ++i)
	{
		sorted = true;

		if (forward)
		{
			for (size_t j = i + 1; j < mas.size() - index; ++j)
			{
				if (mas[j] < mas[j - 1])
				{
					std::swap(mas[j], mas[j - 1]);
					sorted = false;

					print_mas(mas, speed);
				}
			}
			++index;
		}
		else
		{
			for (size_t j = mas.size() - 1 - i; j > i - index; --j)
			{
				if (mas[j] < mas[j - 1])
				{
					std::swap(mas[j], mas[j - 1]);
					sorted = false;

					print_mas(mas, speed);
				}
			}
		}
		if (sorted)
			break;

		forward = !forward;
	}
}

void selection_sort(std::vector<int> &mas, size_t speed)
{
	for (size_t i = 0; i != mas.size(); ++i)
	{
		int min = mas[i];
		size_t minIndex = i;

		for (size_t j = i + 1; j != mas.size(); ++j)
		{
			if (mas[j] < min)
			{
				min = mas[j];
				minIndex = j;
			}
		}

		auto tmp = mas[i];
		mas[i] = min;
		mas[minIndex] = tmp;

		print_mas(mas, speed);
	}
}

void insertion_sort(std::vector<int> &mas, size_t speed)
{
	int tmp, j;

	for (size_t i = 1; i != mas.size(); ++i)
	{

		tmp = mas[i];
		j = i - 1;

		while(j >= 0 && mas[j] > tmp)
		{
			mas[j + 1] = mas[j];
			mas[j] = tmp;
			j--;
		}

		print_mas(mas, speed);
	}
}

void quick_sort_ranged(int *beg, int *end, size_t speed)
{
	if (end - beg < 2)
		return;

	auto p = *(beg + (end - beg) / 2);

	int i = 0, j = end - beg, temp;

	while (i < j)
	{
		while (*(beg + i) < p)
		{
			++i;
		}

		while (*(beg + j) > p)
		{
			--j;
		}

		temp = *(beg + i);
		*(beg + i) = *(beg + j);
		*(beg + j) = temp;

		i++;
		j--;

		print_mas(beg, end, speed);
	}

	quick_sort_ranged(beg, beg + j, speed);
	quick_sort_ranged(beg + j + 1, end, speed);
}

void quick_sort(std::vector<int> &mas, size_t speed)
{
	quick_sort_ranged(&mas.front(), &mas.back(), speed);
}

void run_sort(data_t &data)
{
	cout << data.name << endl;

	if (data.mas.size() <= 40)
	{
		std::for_each(data.mas.begin(), data.mas.end(), [](auto &val) {cout << std::setw(2) << val; });
		cout << endl;
	}

	auto startTime = clock();

	data.func(data.mas, data.speed);

	auto endTime = clock();

	if (data.mas.size() <= 40)
	{
		std::for_each(data.mas.begin(), data.mas.end(), [](auto &val) {cout << std::setw(2) << val; });
		cout << endl;
	}

	cout << "Elasped time: " << endTime - startTime << endl;

	while (clock() - endTime < 1000)
		;
}

int main()
{
	std::default_random_engine rand_eng;
	std::uniform_int_distribution<unsigned> u_ch(0, max_num);

	vector<data_t> vec;

	vector<int> mas(N);

	for (size_t i = 0; i != N; ++i)
	{
		mas[i] = u_ch(rand_eng);
	}

	size_t speed = 10;

	vec.push_back(data_t{ mas, bubble_sort, "bubble_sort", speed / 1});
	vec.push_back(data_t{ mas, shaker_sort, "shaker_sort", speed / 1 });
	vec.push_back(data_t{ mas, selection_sort, "selection_sort", speed });
	vec.push_back(data_t{ mas, insertion_sort, "insertion_sort", speed });
	vec.push_back(data_t{ mas, quick_sort, "qsort", speed });

	std::for_each(vec.begin(), vec.end(), run_sort);

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
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
#include <valarray>
#include <typeinfo>
#include <cctype>
#include <array>
#include <numeric>
#include <math.h>
#include <utility>
#include <iomanip>

#include "../Mas.h"

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
constexpr char min_num = 'A', max_num = 'P';

template <typename T>
struct data_t
{
	std::vector<T> mas;
	//std::function<void(std::vector<T> &, size_t)> func;
	void (*func)(std::vector<T>&, size_t);
	string name;
	size_t speed;
};

vector<string> svec;
size_t cnt_comparison = 0, cnt_swap = 0;

template <typename T>
void bubble_sort(std::vector<T> &mas, size_t speed)
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
				++cnt_swap;

				print_mas(max_num, min_num, mas, N, speed, "bubble_sort " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));
			}
			++cnt_comparison;
		}
		if(sorted)
			break;
	}

	print_mas(max_num, min_num, mas, N, speed, "bubble_sort " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));
}

template <typename T>
void shaker_sort(vector<T> &mas, size_t speed)
{
	bool sorted = false;
	bool forward = false;
	
	size_t index = 0;

	for (size_t i = 0; i != mas.size() - 1; ++i)
	{
		sorted = true;

		if (forward)
		{
			for (size_t j = i + 1 - index; j < mas.size() - index; ++j)
			{
				if (mas[j] < mas[j - 1])
				{
					std::swap(mas[j], mas[j - 1]);
					sorted = false;
					++cnt_swap;

					print_mas(max_num, min_num, mas, N, speed, "shaker_sort " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));
				}
				++cnt_comparison;
			}
			++index;
		}
		else
		{
			for (size_t j = mas.size() - 1 - i + index; j > i - index; --j)
			{
				if (mas[j] < mas[j - 1])
				{
					std::swap(mas[j], mas[j - 1]);
					sorted = false;
					++cnt_swap;

					print_mas(max_num, min_num, mas, N, speed, "shaker_sort " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));
				}
				++cnt_comparison;
			}
		}
		if (sorted)
			break;

		forward = !forward;
	}

	print_mas(max_num, min_num, mas, N, speed, "shaker_sort " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));
}

template <typename T>
void selection_sort(std::vector<T> &mas, size_t speed)
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

		print_mas(max_num, min_num, mas, N, speed, "selection_sort " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));
	}
}

template <typename T>
void insertion_sort(std::vector<T> &mas, size_t speed)
{
	int tmp, j;

	for (int i = 1; i != mas.size(); ++i)
	{

		tmp = mas[i];
		j = i - 1;

		while(j >= 0 && mas[j] > tmp)
		{
			mas[j + 1] = mas[j];
			mas[j] = tmp;
			j--;

			print_mas(max_num, min_num, mas, N, speed, "insertion_sort " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));
		}

		print_mas(max_num, min_num, mas, N, speed, "insertion_sort " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));
	}
}

template <typename T>
void shall_sort(vector<T>& mas, size_t speed)
{
	int h;

	for (h = 1; h <= (mas.size() - 2) / 9; h = 3 * h + 1)
		;
	for (; h > 0; h /= 3)
		for (int i = h; i <= mas.size() - 1; ++i)
		{
			int j = i;
			auto v = mas[i];

			while (j >= h && v < mas[j - h])
			{
				mas[j] = mas[j - h];
				j -= h;

				++cnt_swap;

				print_mas(max_num, min_num, mas, N, speed, "shall_sort " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));
			}
			++cnt_comparison;

			mas[j] = v;

			print_mas(max_num, min_num, mas, N, speed, "shall_sort " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));
		}
}

template <typename T>
void quick_sort_ranged(T *beg, T *end, size_t speed)
{
	if (end - beg < 2)
		return;

	auto p = *(beg + (end - beg) / 2);

	int i = 0, temp;
	auto j = end - beg;

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

		print_mas(max_num, min_num, beg, end, N, speed, "quick_sort_ranged");
	}

	quick_sort_ranged(beg, beg + j, speed);
	quick_sort_ranged(beg + j + 1, end, speed);
}

template <typename T>
void quick_sort(std::vector<T> &mas, size_t speed)
{
	quick_sort_ranged(&mas.front(), &mas.back(), speed);
}

template <typename T>
void run_sort(data_t<T> &data)
{
	cnt_comparison = cnt_swap = 0;

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

	svec.push_back("Elasped time: " + std::to_string(endTime - startTime) + " " + data.name + " " + std::to_string(cnt_comparison) + " " + std::to_string(cnt_swap));

	while (clock() - endTime < 1000)
		;
}

int main()
{
	std::default_random_engine rand_eng;
	std::uniform_int_distribution<> u_ch(min_num, max_num);

	vector<data_t<char>> vec;

	vector<char> mas(N);

	for (size_t i = 0; i != N; ++i)
	{
		mas[i] = u_ch(rand_eng);
		//mas[i] = 'A'/* + i % (max_num - min_num + 1)*/;
	}

	size_t speed = 100;

	vec.push_back(data_t<char>{ mas, bubble_sort<char>, "bubble_sort", speed / 1});
	vec.push_back(data_t<char>{ mas, shaker_sort<char>, "shaker_sort", speed / 1 });
	vec.push_back(data_t<char>{ mas, selection_sort<char>, "selection_sort", speed / 1});
	vec.push_back(data_t<char>{ mas, insertion_sort<char>, "insertion_sort", speed / 1});
	vec.push_back(data_t<char>{ mas, shall_sort<char>, "shall_sort", speed / 1 });
	vec.push_back(data_t<char>{ mas, quick_sort<char>, "qsort", speed / 1});

	std::for_each(vec.begin(), vec.end(), run_sort<char>);

	std::system("clear");

	for (const auto& str : svec)
	{
		cout << str << endl;
	}

	/*cout << "press any key to exit\n";
	
	char ch;
	cin >> ch;*/

	return 0;
}
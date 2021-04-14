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

#define PRINT_SORT
#include "sort.h"

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

const size_t N = 40;
const char min_num = 'A', max_num = 'Z';

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

template <typename T>
void run_sort(data_t<T> &data)
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

	svec.push_back("Elasped time: " + std::to_string(endTime - startTime) + " " + data.name);

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

	size_t speed = 10;

	vec.push_back(data_t<char>{ mas, bubble_sort<char>, "bubble_sort", speed / 1});
	vec.push_back(data_t<char>{ mas, shaker_sort<char>, "shaker_sort", speed / 1 });
	vec.push_back(data_t<char>{ mas, selection_sort<char>, "selection_sort", speed * 10});
	vec.push_back(data_t<char>{ mas, insertion_sort<char>, "insertion_sort", speed * 10});
	vec.push_back(data_t<char>{ mas, shall_sort<char>, "shall_sort", speed * 1 });
	vec.push_back(data_t<char>{ mas, quick_sort<char>, "qsort", speed * 10});

	std::for_each(vec.begin(), vec.end(), run_sort<char>);

	if(std::system("clear")) {

	}

	for (const auto& str : svec)
	{
		cout << str << endl;
	}

	return 0;
}
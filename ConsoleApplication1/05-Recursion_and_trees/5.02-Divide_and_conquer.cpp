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

template <typename T, typename M>
T f_5_16(M beg, M end)
{
	if (beg + 1 >= end)
		return *beg;

	T u = f_5_16<T>(beg + 1, end);

	if (*beg > u)
		return *beg;

	return u;
}

void ex_5_16()
{
	vector<int> ivec;
	
	for (size_t i = 0; i != 10; ++i)
		ivec.push_back(rand() % 100);

	for(auto &i : ivec)
	{
		cout << i << endl;
	}

	cout << "==\n";

	cout << f_5_16<int>(ivec.begin(), ivec.end()) << endl;
}

template <typename T, typename M>
T f_5_17(const M ptr)
{
	if (!ptr->next)
		return ptr->item;

	T u = f_5_17<T>(ptr->next);

	if (ptr->item > u)
		return ptr->item;

	return u;
}

void ex_5_17()
{
	auto ptr = generateRandList<int>(10, 100);

	printList(ptr);

	cout << "==\n";

	cout << f_5_17<int>(ptr) << endl;

	cout << "==\n";

	printList(ptr);
}

template <typename T, typename M>
T f_5_18(M beg, M end)
{
	if (beg + 1 >= end)
		return *beg;

	size_t size = end - beg;

	auto t = log2(size);

	auto x = std::ceil(t);

	size_t mid = static_cast<unsigned>(std::pow(2, x - 1));

	T u = f_5_16<T>(beg, beg + mid);
	T v = f_5_16<T>(beg + mid, end);

	if (u > v)
		return u;

	return v;
}

void ex_5_18()
{
	vector<int> ivec;

	for (size_t i = 0; i != 10; ++i)
		ivec.push_back(rand() % 100);

	for (auto &i : ivec)
	{
		cout << i << endl;
	}

	cout << "==\n";

	cout << f_5_18<int>(ivec.begin(), ivec.end()) << endl;
}

size_t f_5_22(const int max_marks, const size_t num_mark, size_t h)
{
	if (h == 1)
		return 1;

	size_t mid = max_marks / 2;

	if (num_mark == mid)
		return h;
	else if (num_mark < mid)
		return f_5_22(mid, num_mark, h /2);
	else
		return f_5_22(mid, num_mark % mid, h / 2);
}

void ex_5_22()
{
	const size_t n = 4;

	const size_t N = static_cast<unsigned>(pow(2, n));

	for (size_t i = 1; i != N; ++i)
	{
		//cout << std::setw(2) << i << " " << f_5_22(N, i, n) << endl;
		auto size = f_5_22(N, i, N / 2);

		cout << string(size, '-') << endl;
	}
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_5_22();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
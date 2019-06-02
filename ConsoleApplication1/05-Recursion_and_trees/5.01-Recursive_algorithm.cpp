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

double fact_lg(int x)
{
	if (x == 1)
		return 0;
	return log2(x) + fact_lg(x - 1);
}

void ex_5_01()
{
	cout << fact_lg(2) << endl;
}

int fact(int x, int m)
{
	if (x >= m)
		return 0;
	return (fact(x - 1, m) % m) * x % m;
}

void ex_5_02()
{
	cout << fact(1000, 997) << endl;
}

int puzzle(int N)
{
	cout << N << endl;

	if (N == 1)
		return 1;
	if (N % 2 == 0)
		return puzzle(N / 2);
	else
		return puzzle(3 * N + 1);
}

void ex_5_03()
{
	for (size_t i = 1; i != 10; ++i)
	{
		puzzle(i);
		cout << "========\n";
	}
}

int puzzle(int N, int & cnt)
{
	++cnt;

	if (N == 1)
		return 1;
	if (N % 2 == 0)
		return puzzle(N / 2, cnt);
	else
		return puzzle(3 * N + 1, cnt);
}
void ex_5_04()
{
	int maxN = 0, max_i = 0;

	for (size_t i = 1; i != 100; ++i)
	{
		int cnt = 0;

		puzzle(i, cnt);

		if (cnt > maxN)
		{
			maxN = cnt;
			max_i = i;
		}
	}

	cout << max_i << " " << maxN << endl;
}

void ex_5_05()
{
	int m = 55, n = 89;

	auto cur_x = m, cur_n = n;
	int res = 0;

	while (cur_n != 0)
	{
		cout << cur_x << " " << cur_n << endl;
	
		auto tmp = cur_n;

		cur_n = cur_x % cur_n;
		cur_x = tmp;
	}

	res = cur_x;

	cout << res << endl;
}

int eval(const char *a, int &i)
{
	static int offset = -1;

	++offset;

	for (size_t i = 0; i != offset; ++i)
		cout << ' ';

	int x = 0;

	while (a[i] == ' ')
		++i;
	if (a[i] == '+')
	{
		cout << a + i << endl;

		++i;
		auto res = eval(a, i) + eval(a, i);

		for (size_t i = 0; i != offset; ++i)
			cout << ' ';

		cout << "return = " << res << endl;
		--offset;
		return res;
	}
	if (a[i] == '*')
	{
		cout << a + i << endl;

		++i;
		auto res = eval(a, i) * eval(a, i);

		for (size_t i = 0; i != offset; ++i)
			cout << ' ';

		cout << "return = " << res << endl;
		--offset;
		return res;
	}
	while (a[i] >= '0' && a[i] <= '9')
	{
		x = x * 10 + (a[i++] - '0');
	}

	cout << x << endl;

	--offset;

	return x;
}

void ex_5_08()
{
	int i = 0;
	cout << eval("*+7**4 6+ 8 9 5", i) << endl;

	i = 0;
	cout << eval("+**12 12 12 144", i) << endl;
}

int eval_postfix(const char *a, int &i, char &op)
{
	int x = 0;

	while (a[i] == ' ')
	{
		++i;
	}
	if (!a[i])
	{
		op = 0;
		return 0;
	}
	if (a[i] == '+')
	{
		op = '+';
		return 0;
	}
	if (a[i] == '*')
	{
		op = '*';
		return 0;
	}
	while (a[i] >= '0' && a[i] <= '9')
	{
		x = x * 10 + (a[i++] - '0');
	}

	char new_op = ' ';

	while (new_op != 0)
	{
		++i;
		auto res = eval_postfix(a, i, new_op);

		if (res == 0)
		{
			op = new_op;
			return x;
		}
		else if (new_op == '+')
		{
			x = x + res;
		}
		else if (new_op == '*')
		{
			x = x * res;
		}
	}

	return x;
}

void ex_5_09()
{
	int i = 0;
	char ch = ' ';
	cout << eval_postfix("5 9 8 + 4 6 * * 7 + *", i, ch) << endl;
}

int eval_infix(const char *a, int &i)
{
	int x = 0;

	while (a[i])
	{
		while (a[i] == ' ')
		{
			++i;
		}

		int res = 0;

		if (a[i] == '(')
		{
			x = eval_infix(a, ++i);
		}
		else if (a[i] == ')')
		{
			++i;
			return x;
		}
		else if (a[i] >= '0' && a[i] <= '9')
		{
			while (a[i] >= '0' && a[i] <= '9')
			{
				x = x * 10 + (a[i++] - '0');
			}
		}
		else if (a[i] == '+')
		{
			res = eval_infix(a, ++i);

			x += res;
		}
		else if (a[i] == '*')
		{
			res = eval_infix(a, ++i);

			x *= res;
		}
	}

	return x;
}

void ex_5_10()
{
	int i = 0;

	cout << eval_infix("(2 + (5 * (6 + 1)))", i) << endl;
}

string transform_postfix_to_infix(const char *a, int &i)
{
	string x;	

	while (a[i])
	{
		while (a[i] == ' ')
		{
			++i;
		}

		if (a[i] >= '0' && a[i] <= '9')
		{
			while (a[i] >= '0' && a[i] <= '9')
			{
				x += a[i++];
			}

			while (a[i])
			{
				auto res = transform_postfix_to_infix(a, i);

				if (res == "+")
					return res + x + ')';
				else if (res == "*")
					return res + x + ')';

				x = '(' + x + res;
			}
		}
		else if (a[i] == '+')
		{
			return string(1, a[i++]);
		}
		else if (a[i] == '*')
		{
			return string(1, a[i++]);
		}
	}

	return x;
}

void ex_5_12()
{
	int i = 0;

	cout << transform_postfix_to_infix("5 9 8 + 4 6 * * 7 + *", i) << endl;
}

template <typename T>
T f_5_13(link<T> ptr)
{
	if (ptr == ptr->next)
		return ptr->item;

	for (size_t i = 0; i != 5; ++i)
		ptr = ptr->next;
	ptr->next = ptr->next->next;

	cout << "==\n";
	printList(ptr);

	return f_5_13(ptr);
}

void ex_5_13()
{
	link<int> ptr = generateCircularList<int>(10, 0);

	printList(ptr);

	cout << f_5_13(ptr) << endl;
}

template <typename T>
void f_5_14(link<T> ptr)
{
	if (!ptr->next->next)
	{
		ptr->next = nullptr;

		return;
	}

	return f_5_14(ptr->next);
}

void ex_5_14()
{
	link<int> ptr = generateList<int>(10, 0);

	printList(ptr);

	cout << "==\n";

	f_5_14(ptr);

	printList(ptr);
}

template <typename T>
link<T> f_5_15(link<T> ptr, link<T> &prev_ptr)
{
	auto t = ptr->next;

	ptr->next = prev_ptr;

	if (!t)
	{
		return ptr;
	}

	prev_ptr = ptr;

	return f_5_15(t, prev_ptr);
}

void ex_5_15()
{
	link<int> ptr = generateList<int>(10, 0);

	printList(ptr);

	cout << "==\n";

	link<int> prev_ptr = nullptr;

	ptr = f_5_15(ptr, prev_ptr);

	printList(ptr);
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_5_15();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
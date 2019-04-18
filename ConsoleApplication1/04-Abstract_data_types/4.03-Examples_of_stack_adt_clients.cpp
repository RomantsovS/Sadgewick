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

#include "../Stack.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

void ex_4_05()
{
	string a = "5 9 8 + 4 6 * * 7 + *";

	Stack<int> save;

	for (size_t i = 0; i != a.size(); ++i)
	{
		if (a[i] == '+')
			save.push(save.pop() + save.pop());
		else if (a[i] == '*')
			save.push(save.pop() * save.pop());
		else if (a[i] >= '0' && a[i] <= '9')
			save.push(0);

		while( a[i] >= '0' && a[i] <= '9')
			save.push(10 * save.pop() + (a[i++] - '0'));
	}

	cout << save.pop() << endl;
}

void ex_4_06()
{
	string a = "(5*(((9+8)*(4*6))+7))";

	Stack<char> save;

	for (size_t i = 0; i <= a.size(); ++i)
	{
		if (a[i] == ')')
			cout << save.pop() << " ";
		else if (a[i] == '+' || a[i] == '*')
			save.push(a[i]);
		else if (a[i] >= '0' && a[i] <= '9')
			cout << a[i] << " ";
	}

	cout << endl;
}

void ex_4_14()
{
	string a = "(5*(((9-8)/(4*6))+7))", res;

	res.reserve(a.size());

	Stack<char> save;

	for (size_t i = 0; i <= a.size(); ++i)
	{
		if (a[i] == ')')
			res.append(1, save.pop()).append(1, ' ');
		else if (a[i] == '+' || a[i] == '*' || a[i] == '-' || a[i] == '/')
			save.push(a[i]);
		else if (a[i] >= '0' && a[i] <= '9')
			res.append(1, a[i]).append(1, ' ');
	}

	cout << res << endl;

	a = res;

	Stack<int> ops;

	for (size_t i = 0; i != a.size(); ++i)
	{
		if (a[i] == '+')
			ops.push(ops.pop() + ops.pop());
		else if (a[i] == '*')
			ops.push(ops.pop() * ops.pop());
		else if (a[i] == '-')
		{
			auto second = ops.pop();
			ops.push(ops.pop()  - second);
		}
		else if (a[i] == '/')
		{
			auto second = ops.pop();
			ops.push(ops.pop() / second);
		}
		else if (a[i] >= '0' && a[i] <= '9')
			ops.push(0);

		while (a[i] >= '0' && a[i] <= '9')
			ops.push(10 * ops.pop() + (a[i++] - '0'));
	}

	cout << ops.pop() << endl;
}

void ex_4_15()
{
	string a = "-1", res;

	res.reserve(a.size());

	Stack<char> save;

	for (size_t i = 0; i != a.size(); ++i)
	{
		if (a[i] == ')')
			res.append(1, save.pop()).append(1, ' ');
		else if (a[i] == '+' || a[i] == '*' || a[i] == '-' || a[i] == '/')
			save.push(a[i]);
		else if (a[i] >= '0' && a[i] <= '9')
			res.append(1, a[i]).append(1, ' ');
	}

	cout << res << endl;

	a = res;

	Stack<int> ops;

	for (size_t i = 0; i != a.size(); ++i)
	{
		if (a[i] == '+')
			ops.push(ops.pop() + ops.pop());
		else if (a[i] == '*')
			ops.push(ops.pop() * ops.pop());
		else if (a[i] == '-')
		{
			auto second = ops.pop();
			ops.push(ops.pop() - second);
		}
		else if (a[i] == '/')
		{
			auto second = ops.pop();
			ops.push(ops.pop() / second);
		}
		else if (a[i] >= '0' && a[i] <= '9')
			ops.push(0);

		while (a[i] >= '0' && a[i] <= '9')
			ops.push(10 * ops.pop() + (a[i++] - '0'));
	}

	cout << ops.pop() << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_4_15();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
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

string transform_infix_to_postfix(const string &a)
{
	string res;
	res.reserve(a.size());

	Stack<char> save;

	bool last_char_closing_bracket = false;

	for (size_t i = 0; i != a.size(); ++i)
	{
		if (a[i] == ' ')
			continue;

		if (a[i] == ')')
		{
			while (!save.empty() && save.back() != '(')
			{
				res.append(1, save.pop());
			}

			if (!save.empty() && save.back() == '(')
			{
				save.pop();

				if (!save.empty() && save.back() == '$')
				{
					res.append(1, save.pop());
				}
			}
			last_char_closing_bracket = true;
		}
		else if (a[i] == '-' && !last_char_closing_bracket)
		{
			res += "0 ";

			save.push(a[i]);
		}
		else if (a[i] == '(')
		{
			save.push(a[i]);
		}
		else if (a[i] == '+' || a[i] == '*' || a[i] == '/' || a[i] == '-')
		{
			if (!save.empty() && save.back() == '-')
			{
				res += save.pop();
			}

			save.push(a[i]);
		}
		else if (a[i] == '$')
		{
			save.push(a[i]);
		}
		else if (a[i] >= '0' && a[i] <= '9')
		{
			while(i < a.size() && a[i] >= '0' && a[i] <= '9')
				res.append(1, a[i++]);

			res.append(1, ' ');
			--i;
		}
		else if (a[i] == '$')
		{
			save.push(a[i]);
		}

		if (a[i] != ')')
			last_char_closing_bracket = false;
	}

	while (!save.empty())
	{
		res += save.pop();
	}

	return res;
}

template<typename T>
T calc_postfix_expression(const string &res)
{
	Stack<T> ops;

	for (size_t i = 0; i != res.size(); ++i)
	{
		if (res[i] == '+')
			ops.push(ops.pop() + ops.pop());
		else if (res[i] == '*')
			ops.push(ops.pop() * ops.pop());
		else if (res[i] == '-')
		{
			auto second = ops.pop();
			ops.push(ops.pop() - second);
		}
		else if (res[i] == '/')
		{
			auto second = ops.pop();
			ops.push(ops.pop() / second);
		}
		else if (res[i] == '$')
		{
			ops.push(sqrt(ops.pop()));
		}
		else if (res[i] >= '0' && res[i] <= '9')
			ops.push(0);

		while (res[i] >= '0' && res[i] <= '9')
			ops.push(10 * ops.pop() + (res[i++] - '0'));
	}

	return ops.pop();
}

void ex_4_15()
{
	string a = "((-(-1)) + $(((-1) * (-1))-(4 * (-1)))) / 2";

	auto postfix = transform_infix_to_postfix(a);

	cout << postfix << endl;

	auto res = calc_postfix_expression<double>(postfix);

	cout << res << endl;
}

string transform_postfix_to_infix(const string &a)
{
	string res;
	res.reserve(a.size());

	Stack<char> ops, res_stack;

	for (size_t i = 0; i != a.size(); ++i)
	{
		if (a[i] == '+' || a[i] == '*' || a[i] == '-' || a[i] == '/')
		{
			Stack<char> temp;

			while (!ops.empty() && ops.back() == ' ')
			{
				ops.pop();
			}

			if (res_stack.empty())
			{
				res_stack.push(')');

				while (!ops.empty() && ops.back() != ' ')
				{
					res_stack.push(ops.pop());
				}

				res_stack.push(a[i]);

				while (!ops.empty() && ops.back() == ' ')
				{
					ops.pop();
				}

				while (!ops.empty() && ops.back() != ' ')
				{
					res_stack.push(ops.pop());
				}

				res_stack.push('(');
			}
			else
			{
				while (!res_stack.empty())
					temp.push(res_stack.pop());

				res_stack.push(')');

				while (!ops.empty() && ops.back() != ' ')
				{
					res_stack.push(ops.pop());
				}

				res_stack.push(a[i]);

				while (!temp.empty() && temp.back() != ' ')
				{
					res_stack.push(temp.pop());
				}

				res_stack.push('(');
			}
		}
		else if (a[i] >= '0' && a[i] <= '9')
			ops.push(a[i]);
		else if (a[i] == ' ')
			ops.push(a[i]);
	}

	while (!res_stack.empty())
	{
		res += res_stack.pop();
	}

	return res;
}

void ex_4_18()
{
	string a = "-(-100 * -10)";

	cout << a << endl;

	auto postfix = transform_infix_to_postfix(a);

	cout << postfix << " = " << calc_postfix_expression<double>(postfix) << endl;

	auto infix = transform_postfix_to_infix(postfix);

	cout << infix << endl;

	postfix = transform_infix_to_postfix(infix);

	//cout << postfix << " = " << calc_postfix_expression<double>(postfix) << endl;

	cout << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_4_18();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
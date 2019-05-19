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
#include <deque>

#include "../Complex.h"
#include "../Stack.h"
#include "../Queue.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

void ex_4_63()
{
	const int N = 8;

	for (size_t k = 0; k != N; ++k)
	{
		float theta = 2.0f * 3.14159f * k / N;

		Complex t(cos(theta), sin(theta)), x = t;

		cout << k << ": " << t << " ";

		for (size_t j = 0; j != N - 1; ++j)
			x *= t;

		cout << x << endl;
	}

	Complex c1(0.2f, 0.3f), c2(0.4f, 0.6f);

	cout << c1 + c2 << endl;

	c1 += c2;

	cout << c1 << endl;

	cout << endl;
}

void ex_4_72()
{
	Queue<char> st(20);

	st.put('a');
	st.put('b');

	auto st2(st);

	while (!st2.empty())
		cout << st2.get() << endl;

	cout << "===========\n";

	st2 = st;

	while (!st2.empty())
		cout << st2.get() << endl;

	cout << "===========\n";

	while (!st.empty())
		cout << st.get() << endl;

	cout << "=====================\n";

	QueueList<char> st3;

	st3.put('a');
	st3.put('b');

	auto st4(st3);

	while (!st4.empty())
		cout << st4.get() << endl;

	cout << "===========\n";

	st4 = st3;

	while (!st4.empty())
		cout << st4.get() << endl;

	cout << "===========\n";

	while (!st3.empty())
		cout << st3.get() << endl;
}

void ex_4_74()
{
	Stack<char> st3(10);

	st3.push('a');
	st3.push('b');

	auto st4(st3);

	while (!st4.empty())
		cout << st4.pop() << endl;

	cout << "===========\n";

	st4 = st3;

	while (!st4.empty())
		cout << st4.pop() << endl;

	cout << "===========\n";

	while (!st3.empty())
		cout << st3.pop() << endl;
}

void ex_4_75()
{
	StackList<char> st3(20);

	st3.push('a');
	st3.push('b');

	auto st4(st3);

	while (!st4.empty())
		cout << st4.pop() << endl;

	cout << "===========\n";

	st4 = st3;

	while (!st4.empty())
		cout << st4.pop() << endl;

	cout << "===========\n";

	while (!st3.empty())
		cout << st3.pop() << endl;
}

Complex calc_postfix_expression(const string &res)
{
	Stack<Complex> ops(res.size());

	for (size_t i = 0; i != res.size(); ++i)
	{
		if (res[i] == '+' && res[i - 1] == ' ')
			ops.push(ops.pop() + ops.pop());
		else if (res[i] == '*')
			ops.push(ops.pop() * ops.pop());
		else if (res[i] == '-' && res[i - 1] == ' ')
		{
			auto second = ops.pop();
			ops.push(ops.pop() - second);
		}
		/*else if (res[i] == '/')
		{
			auto second = ops.pop();
			ops.push(ops.pop() / second);
		}
		else if (res[i] == '$')
		{
			ops.push(sqrt(ops.pop()));
		}*/
		else if (res[i] >= '0' && res[i] <= '9')
		{
			Stack<float> temp(4);

			temp.push(0);

			while (res[i] >= '0' && res[i] <= '9')
				temp.push(10 * temp.pop() + (res[i++] - '0'));

			int multiple = 1;

			if (res[i] == '-')
				multiple = -1;

			++i;

			temp.push(0);

			while (res[i] >= '0' && res[i] <= '9')
				temp.push(10 * temp.pop() + (res[i++] - '0'));

			auto last = multiple * temp.pop();

			ops.push(Complex(temp.pop(), last));
		}
	}

	return ops.pop();
}

void ex_4_76()
{
	const string str = "1+2i 0+1i + 1-2i * 3+4i +";

	auto res = calc_postfix_expression(str);

	cout << res << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_4_76();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
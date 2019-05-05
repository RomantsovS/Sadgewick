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

#include "../Queue.h"
#include "../Deque.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

void ex_4_36()
{
	Queue<char> q(10);

	q.put('f');
	q.put('i');
	q.put('r');
	q.put('s');
	
	cout << q.get() << endl;
}

void ex_4_37()
{
	string str("EAS*Y*QUE***ST***IO*N***");

	Queue<char> q(10);

	for (const auto ch : str)
	{
		if (ch == '*')
			cout << q.get();
		else
			q.put(ch);
	}

	cout << endl;
}

void ex_4_40()
{
	string str("EAs+Y+QUE**+st+*+IO*n++*");

	Deque<char> q(10);

	for (const auto ch : str)
	{
		if (ch >= 'A' && ch <= 'Z')
			q.put_begin(ch);
		else if (ch >= 'a' && ch <= 'z')
			q.put_end(ch);
		else if (ch == '+')
			cout << q.get_begin();
		else if (ch == '*')
			cout << q.get_end();
	}

	cout << endl;
}

void ex_4_41()
{
	string str("Ea*s*Y++"); //

	Deque<char> q(10);

	for (const auto ch : str)
	{
		if (ch >= 'A' && ch <= 'Z')
			q.put_begin(ch);
		else if (ch >= 'a' && ch <= 'z')
			q.put_end(ch);
		else if (ch == '+')
			cout << q.get_begin();
		else if (ch == '*')
			cout << q.get_end();
	}

	cout << endl;
}

void ex_4_42()
{
	const string expr = "EasY", expr2 = "asYE";

	cout << "expr = " << expr << "; expr2 = " << expr2 << endl;

	DequeList<char> q;

	string res;

	auto iter = expr2.cbegin();

	for (const auto ch : expr)
	{
		if (ch >= 'A' && ch <= 'Z')
			q.put_begin(ch);
		else if (ch >= 'a' && ch <= 'z')
			q.put_end(ch);

		res += ch;

		while (!q.empty())
		{
			auto val = q.get_begin();

			if (*iter == val)
			{
				res += +'+';

				if (++iter == expr2.cend())
					break;

				continue;
			}
			else
				q.put_begin(val);

			val = q.get_end();

			if (*iter == val)
			{
				res += '*';

				if (++iter == expr2.cend())
					break;
			}
			else
			{
				q.put_end(val);

				break;
			}
		}
	}

	if (iter == expr2.cend())
	{
		cout << res << endl;
		q.clear();

		for (const auto ch : res)
		{
			if (ch >= 'A' && ch <= 'Z')
				q.put_begin(ch);
			else if (ch >= 'a' && ch <= 'z')
				q.put_end(ch);
			else if (ch == '+')
				cout << q.get_begin();
			else if (ch == '*')
				cout << q.get_end();
		}
	}
	else
		cout << "is not possibly\n";

	cout << endl;
}

void ex_4_48()
{
	DequeUnordered<string> deq(10);

	deq.put("7");
	deq.put("10");
	deq.put("A");

	while (!deq.empty())
		cout << deq.get() << endl;
	cout << endl;
}

void ex_4_49()
{
	DequeListUnordered<string> deq;

	deq.put("7");
	deq.put("10");
	deq.put("A");
	deq.put("K");

	while (!deq.empty())
		cout << deq.get() << endl;

	cout << endl;
}

void ex_4_50()
{
	DequeListUnordered<size_t> deq;

	for (size_t i = 0; i != 100; ++i)
		deq.put(i);

	for (size_t i = 0; i != 5; ++i)
		cout << deq.get() << endl;

	cout << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_4_50();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
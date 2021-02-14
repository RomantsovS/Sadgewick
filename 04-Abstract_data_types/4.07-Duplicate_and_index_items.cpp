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

#include "../Stack.h"
#include "../Deque.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

void ex_4_53()
{
	StackWithoutDuplicate<unsigned char> st('z');

	const string str = "last in first out";

	for (auto ch : str)
		st.push(ch);

	cout << endl;
}

void ex_4_54()
{
	StackWithoutDuplicateIgnoreNew<unsigned char> st('z');

	const string str = "last in first out";

	for (auto ch : str)
		st.push(ch);

	cout << endl;
}

void ex_4_55()
{
	StackWithoutDuplicateDeleteOld<unsigned char> st('z');

	const string str = "last in first out";

	for (auto ch : str)
		st.push(ch);

	while (!st.empty())
		cout << st.pop() << endl;

	cout << endl;
}

void ex_4_56()
{
	StackListWithoutDuplicateIgnoreNew<unsigned char> st('z');

	const string str = "last in first out";

	for (auto ch : str)
		st.push(ch);

	while (!st.empty())
		cout << st.pop() << endl;

	cout << endl;

	StackListWithoutDuplicateDeleteOld<unsigned char> st2('z');

	for (auto ch : str)
		st2.push(ch);

	while (!st2.empty())
		cout << st2.pop() << endl;

	cout << endl;
}

void ex_4_57()
{
	StackDoubleLinkedWithoutDuplicateDeleteOld<unsigned char> st('z');

	const string str = "last in first out";

	for (auto ch : str)
		st.push(ch);

	while (!st.empty())
		cout << st.pop() << endl;

	cout << endl;
}

void ex_4_58()
{
	DequeWithoutDuplicateIgnoreNew<unsigned char> st('z');

	const string str = "first in first out";

	for (auto ch : str)
		st.put_end(ch);

	while (!st.empty())
		cout << st.get_begin() << endl;

	cout << "========================" << endl;

	DequeWithoutDuplicateDeleteOld<unsigned char> st2('z');

	for (auto ch : str)
		st2.put_begin(ch);

	while (!st2.empty())
		cout << st2.get_end() << endl;

	cout << endl;
}

void ex_4_59()
{
	DequeListWithoutDuplicateIgnoreNew<unsigned char> st;

	const string str = "fff";

	for (auto ch : str)
		st.put_begin(ch);

	while (!st.empty())
		cout << st.get_end() << endl;

	cout << "========================" << endl;

	DequeListWithoutDuplicateDeleteOld<unsigned char> st2;

	for (auto ch : str)
		st2.put_end(ch);

	while (!st2.empty())
		cout << st2.get_begin() << endl;

	cout << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_4_59();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
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

void ex_1()
{
	string str = "{(([]))}";
	Stack<char> st(20);

	for (auto ch : str)
	{
		if (ch == '{' || ch == '(' || ch == '[')
		{
			st.push(ch);
		}
		else
		{
			if (ch == '}' && st.back() == '{')
				st.pop();
			else if (ch == ')' && st.back() == '(')
				st.pop();
			else if (ch == ']' && st.back() == '[')
				st.pop();
		}
	}

	cout << st.empty() << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_1();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
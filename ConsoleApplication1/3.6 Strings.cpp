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

void ex3_55()
{
	const size_t N = 100;
	char * str = new char[N + 1];
	vector<size_t> cnt(N, 0);

	cin >> str;

	auto ptr = str;

	for (; *ptr; ++ptr)
		if(std::isalpha(*ptr))
			++cnt[*ptr - 'A'];

	for (size_t i = 0; i != N; ++i)
		if(cnt[i])
			cout << static_cast<char>('A' + i) << " " << cnt[i] << endl;;

	delete str;
}

void ex3_56()
{
	const size_t N = 100;
	char * str = new char[N + 1];

	cin.getline(str, N);

	auto beg = str, end = str + (std::strlen(str) - 1);

	bool is_polindrome = true;

	for (; beg <= end; ++beg, --end)
	{
		if (*beg == ' ')
			++beg;
		if (*end == ' ')
			--end;
		if (*beg != *end)
		{
			is_polindrome = false;
			break;
		}
	}

	cout << is_polindrome << endl;

	delete[] str;
}

char * my_strcpy(const char * in)
{
	auto size = std::strlen(in) + 1;

	char *out = new char[size];

	for(size_t i = 0; (out[i] = in[i]) != 0; ++i)
		;

	return out;
}

char * my_strcat(const char * str1, const char *str2)
{
	auto size = std::strlen(str1) + std::strlen(str2) + 1;

	char *out = new char[size];
	auto ptr = out;

	for (; *str1 != 0; ++str1, ++ptr)
		*ptr = *str1;

	for (; *str2 != 0; ++str2, ++ptr)
		*ptr = *str2;

	++*ptr = '\0';

	return out;
}

void ex3_57()
{
	const size_t N = 100;
	char * str1 = new char[N + 1];
	char * str2 = new char[N + 1];

	cin.getline(str1, N);
	cin.getline(str2, N);

	auto str = my_strcpy(str1);

	cout << str << endl;

	delete[] str;

	str = my_strcat(str1, str2);

	cout << str << endl;

	delete[] str1;
	delete[] str2;

	delete[] str;
}

void ex3_58()
{
	const size_t N = 100;
	const char *str1 = "i love you very much";
	const char *str2 = "lo yo baby";

	std::vector<const char*> svec;

	char *str = new char [N];
	*str = 0;
	auto str_ptr = str;

	for (auto ptr = str2; *ptr != 0; ++ptr)
	{
		if (*ptr == ' ')
		{
			if (*str)
			{
				*str_ptr = 0;
				svec.push_back(my_strcpy(str));
			}
			*str = 0;
			str_ptr = str;
		}
		else
		{
			*str_ptr = *ptr;
			++str_ptr;
		}
	}
	*str_ptr = 0;
	svec.push_back(my_strcpy(str));

	for(auto word : svec)
	{
		for (auto str_ptr = str1; *str_ptr; ++str_ptr)
		{
			auto ptr = word;

			for (; *ptr && *str_ptr == *ptr; ++str_ptr, ++ptr)
				;

			if (!*ptr)
				cout << word << endl;
		}
	}

	delete[] str;
}

void ex3_59()
{
	const size_t N = 100;
	const char *str = "i   love    you    very     much";
	
	char *str1 = new char[std::strlen(str) + 1];
	auto str_ptr = str1;

	for(auto ptr = str; *ptr;)
	{
		*str_ptr++ = *ptr;
		
		if (*ptr == ' ')
			while (*++ptr == ' ')
				;
		else
			++ptr;
	}

	*str_ptr = 0;

	cout << str1 << "!" << endl;

	delete[] str1;
}

void ex3_61()
{
	const size_t N = 100;
	const char *s = "a    bc        difghi j";

	size_t max_scape = 0;
	size_t len = std::strlen(s), n = 0, k, i;

	i = 0;

	while (s[i] != '\0')
	{
		if (s[i] == ' ')
		{
			n = i;

			i += max_scape;

			if (i < len && s[i] == ' ')
			{
				k = i;
				
				while (k > 1 && s[k - 1] == ' ')
				{
					--k;
				}

				while (i < len && s[i] == ' ')
				{
					++i;
				}
				
				if (i - k > max_scape)
					max_scape = i - k;
			}
		}

		if (i < len)
			i++;
		else
			break;
	}

	cout << max_scape << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex3_61();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
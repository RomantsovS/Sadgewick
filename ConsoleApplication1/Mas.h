#ifndef MAS_H
#define MAS_H

#include <vector>
#include <string>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

template <typename T>
void print_mas(T max_num, T min_num, const T* beg, const T* end, size_t N, size_t speed, const string& str = "")
{
	//return;

	//char buffer[(N + 1) * (max_num + 1 + 1)];
	vector<char> buffer;
	buffer.resize((N + 1) * (max_num + 1 + 1));

	memset(&buffer[0], ' ', (N + 1) * (max_num + 1 + 1));

	static clock_t lastClock = clock();

	system("cls");

	char* p_next_write = &buffer[0];

	auto iter = beg;

	for (int j = max_num; j >= min_num; --j)
	{
		iter = beg;
		while (iter < end)
		{
			if (*iter == j)
				*p_next_write = j;
			else
				*p_next_write = ' ';

			p_next_write++;
			++iter;
		}

		*p_next_write++ = '\n';
	}

	std::for_each(beg, end, [&p_next_write](auto& val)
	{*p_next_write++ = val; });

	std::cout.write(&buffer[0], p_next_write - &buffer[0]);

	cout << endl;

	if (!str.empty())
		cout << str + " " << speed << endl;

	while (clock() - lastClock < CLOCKS_PER_SEC / 1000 * static_cast<int>(speed))
		;
	lastClock = clock();
}

template <typename T>
void print_mas(T max_num, T min_num, const vector<T>& mas, size_t N, size_t speed, const string& str = "")
{
	print_mas(max_num, min_num, &mas.front(), &mas.back() + 1, N, speed, str);
}

template <typename T>
void print_mas(const vector<T>& mas)
{

	for (auto& el : mas)
	{
		cout << std::setw(2) << el;
	}
	cout << endl;
}

#endif // !MAS_H


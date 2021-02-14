#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <iomanip>

#include "../Mas.h"

const size_t N = 26;
constexpr char min_num = 'A', max_num = 'Z';

size_t cnt_comparison = 0, cnt_swap = 0;

size_t speed = 100;

template <typename T>
void shall_sort(vector<T> &mas)
{
	int h;

	for (h = 1; h <= (mas.size() - 2) / 9; h = 3 * h + 1)
		;
	for (; h > 0; h /= 3)
		for (int i = h; i <= mas.size() - 1; ++i)
		{
			int j = i;
			auto v = mas[i];

			while (j >= h && v < mas[j - h])
			{
				mas[j] = mas[j - h];
				j -= h;

				++cnt_swap;

				print_mas(max_num, min_num, mas, N, speed, "shall_sort " + std::to_string(h) + " " + std::to_string(i) + " " + std::to_string(j));
			}
			++cnt_comparison;

			mas[j] = v;

			print_mas(max_num, min_num, mas, N, speed, "shall_sort " + std::to_string(h) + " " + std::to_string(i) + " " + std::to_string(j));
		}
}

void ex_6_05()
{
	std::default_random_engine rand_eng;
	std::uniform_int_distribution<> u_ch(min_num, max_num);

	vector<char> mas(N);

	for (size_t i = 0; i != N; ++i)
	{
		mas[i] = u_ch(rand_eng);
		//mas[i] = 'A' + i % (max_num - min_num + 1);
		//mas[i] = 'A';
	}

	print_mas(mas);

	shall_sort(mas);

	print_mas(mas);
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_6_05();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
#include <iostream>
#include <conio.h>
#include <vector>
#include <random>
#include <iomanip>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

template <typename T>
void selection_sort(vector<T> &mas)
{
	for (size_t i = 0; i != mas.size(); ++i)
	{
		size_t min = i;

		for (size_t j = i + 1; j != mas.size(); ++j)
		{
			if (mas[j] < mas[min])
			{
				min = j;
			}
		}

		std::swap(mas[i], mas[min]);
	}
}

template <typename T>
void print_mas(const vector<T> &mas)
{

	for (auto &el : mas)
	{
		cout << std::setw(2) << el << " ";
	}
	cout << endl;
}

void ex_6_2()
{
	const size_t N = 10;

	std::default_random_engine rand_eng;
	std::uniform_int_distribution<unsigned> u_ch(0, 10);

	vector<int> vec;

	vector<int> mas(N);

	for (size_t i = 0; i != N; ++i)
	{
		mas[i] = u_ch(rand_eng);
	}

	print_mas(mas);

	selection_sort(mas);

	print_mas(mas);
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_6_2();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
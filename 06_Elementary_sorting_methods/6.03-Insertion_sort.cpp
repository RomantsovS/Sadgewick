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
void insertion_sort(vector<T> &mas)
{
	for (size_t i = mas.size() - 1; i > 0; --i)
	{
		if (mas[i] < mas[i - 1])
			std::swap(mas[i], mas[i - 1]);
	}

	for (size_t i = 2; i != mas.size(); ++i)
	{
		int j = i;
		T tmp = mas[i];

		while (tmp < mas[j - 1])
		{
			mas[j] = mas[j - 1];
			--j;
		}
		mas[j] = tmp;
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

void ex_6_3()
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

	insertion_sort(mas);

	print_mas(mas);
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_6_3();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
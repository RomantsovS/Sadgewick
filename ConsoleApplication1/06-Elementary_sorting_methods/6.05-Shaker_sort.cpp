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

size_t cnt = 0;

template <typename T>
void shaker_sort(vector<T> &mas)
{
	bool sorted = false;
	bool forward = false;

	for (size_t i = 0; i != mas.size() - 1; ++i)
	{
		sorted = true;

		if (forward)
		{
			for (size_t j = i + 1; j < mas.size(); ++j)
			{
				if (mas[j] < mas[j - 1])
				{
					std::swap(mas[j], mas[j - 1]);
					sorted = false;
				}
				++cnt;
			}
		}
		else
		{
			for (size_t j = mas.size() - 1; j > i; --j)
			{
				if (mas[j] < mas[j - 1])
				{
					std::swap(mas[j], mas[j - 1]);
					sorted = false;
				}
				++cnt;
			}
		}
		if (sorted)
			break;
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

void ex_6_30()
{
	const size_t N = 20;

	std::default_random_engine rand_eng;
	std::uniform_int_distribution<unsigned> u_ch(0, 100);

	vector<int> vec;

	vector<int> mas(N);

	for (size_t i = 0; i != N; ++i)
	{
		mas[i] = u_ch(rand_eng);
	}

	auto copy_mas = mas;

	print_mas(mas);

	shaker_sort(mas);

	print_mas(mas);

	cout << cnt << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_6_30();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
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

const unsigned long maxN = 10000, N = 10;
const size_t d = 2;

template <typename T>
void f(T a, T b)
{
	unsigned long i, N;

	for (N = 3; N != maxN; ++N)
	{
		b[N] = 0;

		for (i = 2; i < N; ++i)
			a[i] = 1;

		for (i = 2; i < N; ++i)
		{
			if (a[i])
				for (int j = i; j * i < N; ++j)
					a[j * i] = 0;
		}

		for (i = 2; i < N; ++i)
			if (a[i])
				b[N]++;
	}

	for (N = 3; N < maxN; N += maxN / 25)
	{
		cout << std::setw(4) << N << " " << std::setw(4) << b[N] << " ";

		for (i = 0; i < b[N]; i += static_cast<unsigned long>(std::ceil(b[maxN - 1] / 80.0)))
			cout << '*';
		cout << endl;
	}
}

bool heads()
{
	return rand() < RAND_MAX * (4.0 / N);
}

float randF()
{
	return 1.0f * rand() / RAND_MAX;
}

template <typename T, size_t N>
struct Point
{
	Point() : pos(N) {}
	void InitRandom()
	{
		for (size_t i = 0; i != N; ++i)
		{
			pos[i] = randF();
		}
	}

	vector<T> pos;
};

template <typename T, size_t N>
float distance(const Point<T, N> &p1, const Point<T, N> &p2)
{
	vector<T> d(N);

	for (size_t i = 0; i != N; ++i)
	{
		d[i] = p1.pos[i] - p2.pos[i];
	}

	T sum = 0;

	for (size_t i = 0; i != N; ++i)
	{
		sum += d[i] * d[i];
	}

	return sqrt(sum);
}

int main()
{
	float d = 0.5;

	int i, cnt = 0;

	Point<float, 2> *a = new Point<float, 2>[N];

	for(i = 0; i != N; ++i)
	{
		a[i].InitRandom();
	}

	for (i = 0; i != N; ++i)
	{
		for (int j = i + 1; j != N; ++j)
			if (distance(a[i], a[j]) < d)
			{
				++cnt;
				//cout << a[i].x << "-" << a[i].y << " - " << a[j].x << "-" << a[j].y << endl;;
			}
	}

	cout << cnt << endl;

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
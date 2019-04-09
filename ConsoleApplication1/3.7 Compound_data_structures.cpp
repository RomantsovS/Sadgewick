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

#include "Point.h"
#include "List.h"

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

int compare(void const* i, void const* j)
{
	return strcmp(*(char**)i, *(char**)j);
}

void ex_3_17()
{
	const int Nmax = 1000;
	const int Mmax = 10000;

	char *a[Nmax];
	int N;
	char buf[Mmax];
	size_t M = 0;
	
	for (N = 0; N < Nmax; ++N)
	{
		a[N] = &buf[M];

		if (!(cin >> a[N]))
			break;

		M += strlen(a[N]) + 1;
	}

	std::qsort(a, N, sizeof(char*), compare);

	for (int i = 0; i != N; ++i)
		cout << a[i] << endl;
}

void ex_3_18()
{
	const size_t V = 10;
	int i, j, adj[V][V];

	for (i = 0; i != V; ++i)
		for (j = 0; j != V; ++j)
			adj[i][j] = 0;

	for (i = 0; i != V; ++i)
		adj[i][i] = 1;

	while (cin >> i >> j)
	{
		adj[i][j] = 1;
		adj[j][i] = 1;
	}
}

static link<Point<float, 2>> **grid;
static int G, cnt = 0;
static float d;

void grid_insert(float x, float y)
{
	int X = static_cast<int>(x * G + 1);
	int Y = static_cast<int>(y * G + 1);

	Point<float, 2> p;
	
	p.pos[0] = x;
	p.pos[1] = y;

	link<Point<float, 2>> s, t = new node<Point<float, 2>>(p, grid[X][Y]);

	for (int i = X - 1; i <= X + 1; ++i)
	{
		for (int j = Y - 1; j <= Y + 1; ++j)
			for (s = grid[i][j]; s != 0; s = s->next)
				if (distance(s->item, t->item) < d)
					++cnt;
	}
	
	grid[X][Y] = t;
}

void ex_3_20()
{
	int i, N = 100;
	d = 0.01f, G = static_cast<int>(1 / d);

	grid = malloc2d<link<Point<float, 2>>>(G + 2, G + 2);

	for (i = 0; i < G + 2; ++i)
		for (int j = 0; j < G + 2; ++j)
			grid[i][j] = 0;
	for (i = 0; i < N; ++i)
		grid_insert(randF(), randF());

	cout << cnt << " pairs within " << d << endl;
}

void ex_3_62()
{
	auto mas3d = malloc3d<int>(3, 4, 5);

	size_t cnt = 0;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				mas3d[i][j][k] = static_cast<std::remove_pointer<std::remove_pointer<std::remove_pointer<decltype(mas3d)>::type>::type>::type>(cnt++);

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			for (int k = 0; k < 5; ++k)
				cout << mas3d[i][j][k];

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
			delete[] mas3d[i][j];

	for (int i = 0; i < 3; ++i)
		delete[] mas3d[i];

	delete[] mas3d;
}

void ex_3_63()
{
	const int Nmax = 1000;

	char *a[Nmax];
	int N;
	char buf[Nmax];
	size_t M = 0;

	for (N = 0; N < Nmax; ++N)
	{
		if (!(cin >> buf))
			break;

		a[N]= new char [strlen(buf) + 1];
		strcpy_s(a[N], strlen(buf) + 1, buf);

		M += strlen(a[N]) + 1;
	}

	std::qsort(a, N, sizeof(char*), compare);

	for (int i = 0; i != N; ++i)
		cout << a[i] << endl;
}

void ex_3_66()
{
	const size_t N = 4, M = 8;

	auto mat2d = malloc2d<int>(N, M);

	for (size_t i = 0; i != N; ++i)
	{
		mat2d[rand() % N][rand() % M] = i + 1;
	}

	print_mat2d(mat2d, N, M);

	cout << "-----------------------" << endl;

	multilist_mat2d<int> m_list(mat2d, N, M);

	m_list.print();

	for (int i = 0; i < N; ++i)
		delete[] mat2d[i];

	delete[] mat2d;
}

void ex_3_67()
{
	size_t N = 4, M = 8;

	Matrix2d<int> mat2d(N, M, 0);

	/*for (size_t i = 0; i != N; ++i)
	{
		mat2d[rand() % N][rand() % M] = i + 1;
	}*/

	mat2d.print();

	cout << "----------" << endl;

	/*multilist_mat2d<int> m_list(mat2d, N, M);

	m_list.print();*/

	cout << "-----------------------" << endl;

	N = 8, M = 3;

	mat2d = Matrix2d<int>(N, M, 0);

	/*for (size_t i = 0; i != N; ++i)
	{
		mat2d[rand() % N][rand() % M] = i + 1;
	}*/

	mat2d.print();

	/*cout << "---------" << endl;

	multilist_mat2d<int> m_list2(mat2d, N, M);

	m_list2.print();*/
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_3_67();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
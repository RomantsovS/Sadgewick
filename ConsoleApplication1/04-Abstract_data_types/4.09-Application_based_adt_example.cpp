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

#include "../Poly.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;

void ex_4_78()
{
	const int n = 1;

	std::shared_ptr<Poly<int>> x = std::make_shared<Poly<int>>(1, 10), one = std::make_shared<Poly<int>>(1, 0);

	cout << *x << " " << x->eval(n) << endl;

	std::shared_ptr<Poly<int>> t = std::make_shared<Poly<int>>(*x + *one);

	cout << *t << " " << t->eval(n) << endl;

	auto y = t;

	for (size_t i = 0; i != 5; ++i)
	{
		y = std::make_shared<Poly<int>>(*y * *t + *t);

		cout << *y << " " << y->eval(n) << endl;
	}

	std::shared_ptr<PolyList<int>> x2 = std::make_shared<PolyList<int>>(1, 10), one2 = std::make_shared<PolyList<int>>(1, 0);

	cout << *x2 << " " << x2->eval(n) << endl;

	std::shared_ptr<PolyList<int>> t2 = std::make_shared<PolyList<int>>(*x2 + *one2);

	cout << *t2 << " " << t2->eval(n) << endl;

	auto y2 = t2;

	for (size_t i = 0; i != 5; ++i)
	{
		y2 = std::make_shared<PolyList<int>>(*y2 * *t2 + *t2);

		cout << *y2 << " " << y2->eval(n) << endl;
	}
}

void ex_4_80()
{
	const int n = 1;

	std::shared_ptr<Poly<int>> x = std::make_shared<Poly<int>>(1, 10), one = std::make_shared<Poly<int>>(1, 0);

	cout << *x << " " << x->eval(n) << endl;

	*x += *x;
	cout << *x << " " << x->eval(n) << endl;

	*one += *x;
	cout << *one << " " << one->eval(n) << endl;

	*x = *one + *one;
	cout << *x << " " << x->eval(n) << endl;

	cout << "======================\n";

	x = std::make_shared<Poly<int>>(1, 10), one = std::make_shared<Poly<int>>(1, 0);

	*x *= *x;
	cout << *x << " " << x->eval(n) << endl;

	*one += *x + *x;
	cout << *one << " " << one->eval(n) << endl;

	*x = *one * *one;
	cout << *x << " " << x->eval(n) << endl;

	cout << "=========================================\n";

	std::shared_ptr<PolyList<int>> x2 = std::make_shared<PolyList<int>>(1, 10), one2 = std::make_shared<PolyList<int>>(1, 0);

	cout << *x2 << " " << x2->eval(n) << endl;

	*x2 += *x2;
	cout << *x2 << " " << x2->eval(n) << endl;

	*one2 += *x2;
	cout << *one2 << " " << one->eval(n) << endl;

	*x2 = *one2 + *one2;
	cout << *x2 << " " << x2->eval(n) << endl;

	cout << "======================\n";

	x2 = std::make_shared<PolyList<int>>(1, 10), one2 = std::make_shared<PolyList<int>>(1, 0);

	*x2 *= *x2;
	cout << *x2 << " " << x2->eval(n) << endl;

	*one2 += *x2 + *x2;
	cout << *one2 << " " << one2->eval(n) << endl;

	*x2 = *one2 * *one2;
	cout << *x2 << " " << x2->eval(n) << endl;
}

void ex_4_81()
{
	const int n = 1;

	std::shared_ptr<Poly<double>> x = std::make_shared<Poly<double>>(1.0, 10), one = std::make_shared<Poly<double>>(1.0, 0);

	cout << *x << " " << x->eval(n) << endl;

	*x += *one;
	cout << *x << " " << x->eval(n) << endl;

	*x *= *x + *one;
	cout << *x << " " << x->eval(n) << endl;

	cout << x->diff() << " " << x->diff().eval(n) << endl;

	cout << "======================\n";

	x = std::make_shared<Poly<double>>(1.0, 10), one = std::make_shared<Poly<double>>(1.0, 0);

	cout << *x << " " << x->eval(n) << endl;

	*x += *one;
	cout << *x << " " << x->eval(n) << endl;

	*x *= *x + *one;
	cout << *x << " " << x->eval(n) << endl;

	cout << x->integr() << " " << x->integr().eval(n) << endl;

	cout << "=========================================\n";

	std::shared_ptr<PolyList<double>> x2 = std::make_shared<PolyList<double>>(1, 10), one2 = std::make_shared<PolyList<double>>(1, 0);

	cout << *x2 << " " << x2->eval(n) << endl;

	*x2 += *one2;
	cout << *x2 << " " << x2->eval(n) << endl;

	*x2 *= *x2 + *one2;
	cout << *x2 << " " << x2->eval(n) << endl;

	cout << x2->diff() << " " << x2->diff().eval(n) << endl;

	cout << "======================\n";

	x2 = std::make_shared<PolyList<double>>(1, 10), one2 = std::make_shared<PolyList<double>>(1, 0);

	cout << *x2 << " " << x2->eval(n) << endl;

	*x2 += *one2;
	cout << *x2 << " " << x2->eval(n) << endl;

	*x2 *= *x2 + *one2;
	cout << *x2 << " " << x2->eval(n) << endl;

	cout << x2->integr() << " " << x2->integr().eval(n) << endl;
}

void ex_4_83()
{
	const int n = 1;

	auto x = Poly<double>(1, 100) + Poly<double>(-12, 2) + Poly<double>(-42, 0);
	cout << x << " " << x.eval(n) << endl;

	auto y = Poly<double>(1, 10) + Poly<double>(-3, 0);
	cout << y << " " << y.eval(n) << endl;

	auto t = x / y;

	cout << t << " " << t.eval(n) << endl;

	cout << "======================\n";

	auto x2 = PolyList<double>(1, 100) + PolyList<double>(-12, 2) + PolyList<double>(-42, 0);
	cout << x2 << " " << x2.eval(n) << endl;

	auto y2 = Poly<double>(1, 10) + Poly<double>(-3, 0);
	cout << y2 << " " << y2.eval(n) << endl;

	auto t2 = x / y;

	cout << t2 << " " << t2.eval(n) << endl;
}

int main()
{
	for (size_t i = 0; i < 1; ++i)
	{
		ex_4_83();
	}

	cout << "press any key to exit\n";
	_getch();

	return 0;
}
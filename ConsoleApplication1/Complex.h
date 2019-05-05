#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

class Complex
{
private:
	float re, im;
public:
	Complex(float x, float y) : re(x), im(y) {}

	float Re() const { return re; }
	float Im() const { return im; }

	Complex& operator *=(const Complex &rhs)
	{
		auto t = Re();

		re = Re() * rhs.Re() - Im() * rhs.Im();
		im = t * rhs.Im() + Im() * rhs.Re();

		return *this;
	}

	Complex& operator +=(const Complex &rhs)
	{
		re = Re() + rhs.Re();
		im = Im() + rhs.Im();

		return *this;
	}
};

std::ostream & operator << (std::ostream &os, const Complex &c)
{
	os << std::fixed;

	cout.precision(3);

	os << std::setw(6) << c.Re() << " " << std::setw(6) << c.Im();

	return os;
}

Complex operator + (const Complex &lhs, const Complex &rhs)
{
	auto res = lhs;

	res += rhs;

	return res;
}

#endif
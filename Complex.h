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
	Complex() = default;
	Complex(float x, float y) : re(x), im(y) {}
	Complex(int x) : re(static_cast<float>(x)), im(0) {}

	float Re() const { return re; }
	float Im() const { return im; }

	float module() const
	{
		return Re() * Re() + Im() * Im();
	}

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

	Complex& operator -=(const Complex &rhs)
	{
		re = Re() - rhs.Re();
		im = Im() - rhs.Im();

		return *this;
	}

	explicit operator char() const
	{
		return 'A' + static_cast<char>(module());
	}
};

std::ostream & operator << (std::ostream &os, const Complex &c)
{
	os << std::fixed;

	cout.precision(3);

	os << std::setw(6) << c.Re() << ((c.Im() > 0) ? " +" : "") << std::setw(6) << c.Im() << "i";

	return os;
}

Complex operator + (const Complex &lhs, const Complex &rhs)
{
	auto res = lhs;

	res += rhs;

	return res;
}

Complex operator - (const Complex &lhs, const Complex &rhs)
{
	auto res = lhs;

	res -= rhs;

	return res;
}

Complex operator * (const Complex &lhs, const Complex &rhs)
{
	float re = lhs.Re() * rhs.Re() - lhs.Im() * rhs.Im();
	float im = lhs.Re() * rhs.Im() + lhs.Im() * rhs.Re();

	return Complex(re, im);
}

bool operator == (const Complex& lhs, const Complex& rhs)
{
	return lhs.module() == rhs.module();
}

bool operator < (const Complex& lhs, const Complex& rhs)
{
	return lhs.module() < rhs.module();
}

#endif
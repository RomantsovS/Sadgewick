#ifndef POINT_H
#define POINT_H

#include <numeric>
#include <math.h>
#include <vector>

using std::cout;
using std::endl;

float randF()
{
	return 1.0f * rand() / RAND_MAX;
}

template<typename T, size_t N> class Point;

template<typename T, size_t N> bool operator==(const Point<T, N> &a, const Point<T, N> &b);
template<typename T, size_t N> bool operator!=(const Point<T, N> &a, const Point<T, N> &b);
template<typename T, size_t N> std::ostream& operator<<(std::ostream &os, const Point<T, N> &b);

template<typename T, size_t N> float distance(const Point<T, N> &p1, const Point<T, N> &p2);

template <typename T, size_t N>
class Point
{
	friend bool operator==<T>(const Point &a, const Point &b);
	friend bool operator!=<T>(const Point &a, const Point &b);

	friend std::ostream& operator<<<T>(std::ostream &os, const Point<T, N> &b);

	friend float distance<T>(const Point<T, N> &p1, const Point<T, N> &p2);
public:
	Point() : pos(N) {}

	void InitRandom()
	{
		for (size_t i = 0; i != N; ++i)
		{
			pos[i] = randF();
		}
	}
private:
	std::vector<T> pos;
};

template <typename T, size_t N>
float distance(const Point<T, N> &p1, const Point<T, N> &p2)
{
	std::vector<T> d(N);

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

#endif

template<typename T, size_t N>
inline bool operator==(const Point<T, N> & a, const Point<T, N> & b)
{
	return distance(a, b) < 0.001;
}

template<typename T, size_t N>
inline bool operator!=(const Point<T, N> & a, const Point<T, N> & b)
{
	return !(a == b);
}

template<typename T, size_t N>
inline std::ostream & operator<<<T>(std::ostream & os, const Point<T, N>& b)
{
	for (const auto p : b.pos)
	{
		cout << p << " ";
	}

	cout << endl;

	return os;
}

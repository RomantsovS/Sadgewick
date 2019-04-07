#ifndef POINT_H
#define POINT_H

#include <numeric>
#include <math.h>
#include <vector>

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
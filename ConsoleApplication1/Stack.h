#ifndef STACK_H
#define STACK_H

#include <numeric>
#include <math.h>
#include <vector>

template <typename T>
class Stack
{
public:
	Stack() {}

	bool empty() const;

	void push(T item);
	T pop();
private:
	std::vector<T> data;
};

template<typename T>
inline bool Stack<T>::empty() const
{
	return data.empty();
}

template<typename T>
inline void Stack<T>::push(T item)
{
	data.push_back(item);
}

template<typename T>
inline T Stack<T>::pop()
{
	auto val = data.back();
	data.pop_back();

	return val;
}

#endif
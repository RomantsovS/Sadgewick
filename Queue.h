#ifndef QUEUE_H
#define QUEUE_H

#include <numeric>
#include <math.h>
#include <vector>
#include <string>

template <typename T>
class Queue
{
public:
	Queue(size_t maxN) : data(new T[maxN + 1]), N(maxN), head(N), tail(0) {}
	Queue(const Queue<T> &rhs);

	Queue<T> & operator=(const Queue<T> &rhs);

	~Queue()
	{
		delete[] data;
	}

	bool empty() const;

	void put(T item);
	T get();
private:
	T *data;
	size_t N, head, tail;
};

template<typename T>
inline Queue<T>::Queue(const Queue<T> & rhs) : data(new T[rhs.N]), N(rhs.N), head(rhs.head), tail(rhs.tail)
{
	for(auto t = head % N; t != tail; ++t)
	{
		data[t] = rhs.data[t];
	}
}

template<typename T>
inline Queue<T>& Queue<T>::operator=(const Queue<T>& rhs)
{
	delete [] data;

	N = rhs.N;
	head = rhs.head;
	tail = rhs.tail;

	data = new T[N];

	for (auto t = head % N; t != tail; ++t)
	{
		data[t] = rhs.data[t];
	}

	return *this;
}

template<typename T>
inline bool Queue<T>::empty() const
{
	return head % N == tail;
}

template<typename T>
inline void Queue<T>::put(T item)
{
	data[tail++] = item;
	tail = tail % N;
}

template<typename T>
inline T Queue<T>::get()
{
	head = head % N;

	return data[head++];
}

template <typename T>
class QueueList
{
private:
	struct node
	{
		node() : next(nullptr) {}
		node(T x) : item(x) {}

		T item;
		std::shared_ptr<node> next;
	};
public:
	QueueList() : head(nullptr), tail(nullptr) {}
	QueueList(const QueueList<T> &rhs);

	QueueList<T> & operator=(const QueueList<T> &rhs);

	bool empty() const;

	void put(T item);
	T get();
private:
	std::shared_ptr<node> head, tail;
};

template<typename T>
inline QueueList<T>::QueueList(const QueueList<T>& rhs)
{
	auto ptr = rhs.head;

	while (ptr)
	{
		put(ptr->item);

		ptr = ptr->next;
	}
}

template<typename T>
inline QueueList<T>& QueueList<T>::operator=(const QueueList<T>& rhs)
{
	auto ptr = rhs.head;

	while (ptr)
	{
		put(ptr->item);

		ptr = ptr->next;
	}

	return *this;
}

template<typename T>
inline bool QueueList<T>::empty() const
{
	return head == nullptr;
}

template<typename T>
inline void QueueList<T>::put(T item)
{
	auto t = tail;

	tail = std::make_shared<node>(item);
	
	if (!head)
	{
		head = tail;
	}
	else
	{
		t->next = tail;
	}
}

template<typename T>
inline T QueueList<T>::get()
{
	auto val = head->item;

	head = head->next;

	return val;
}

#endif
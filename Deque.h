#ifndef DEQUE_H
#define DEQUE_H

#include <numeric>
#include <math.h>
#include <vector>
#include <string>

template <typename T>
class Deque
{
public:
	Deque(size_t maxN) : data(new T[maxN + 1]), N(maxN), head(N), tail(0), count(0) {}
	~Deque()
	{
		delete[] data;
	}

	bool empty() const;
	bool full() const;
	void clear();

	void put_begin(T item);
	void put_end(T item);
	
	T get_begin();
	T get_end();
private:
	T *data;
	size_t N, head, tail, count;
};

template<typename T>
inline bool Deque<T>::empty() const
{
	return count == 0;
}

template<typename T>
inline bool Deque<T>::full() const
{
	return count == N;
}

template<typename T>
inline void Deque<T>::clear()
{
	head = N;
	tail = 0;
}

template<typename T>
inline void Deque<T>::put_begin(T item)
{
	if (full())
	{
		std::cout << "deque is full!\n";
		return;
	}

	head = head % N;

	if (empty())
	{
		data[head] = item;

		++tail;
	}
	else
	{
		if (head == 0)
			head = N - 1;
		else
			--head;

		data[head] = item;
	}

	++count;
}

template<typename T>
inline void Deque<T>::put_end(T item)
{
	if (full())
	{
		std::cout << "deque is full!\n";
		return;
	}

	data[tail++] = item;
	tail = tail % N;

	++count;
}

template<typename T>
inline T Deque<T>::get_begin()
{
	if (empty())
		throw std::out_of_range("deque is empty\n");

	head = head % N;

	--count;

	return data[head++];
}

template<typename T>
inline T Deque<T>::get_end()
{
	if (empty())
		throw std::out_of_range("deque is empty\n");

	if (tail == 0)
		tail = N - 1;
	else
		--tail;

	auto val = data[tail];

	--count;

	return val;
}

template <typename T>
class DequeWithoutDuplicateIgnoreNew
{
public:
	DequeWithoutDuplicateIgnoreNew(size_t maxN) : data(new T[maxN + 1]), N(maxN), head(N), tail(0), count(0) {}
	~DequeWithoutDuplicateIgnoreNew()
	{
		delete[] data;
	}

	bool empty() const;
	bool full() const;
	void clear();

	void put_begin(T item);
	void put_end(T item);

	T get_begin();
	T get_end();
private:
	T *data;
	size_t N, head, tail, count;
};

template<typename T>
inline bool DequeWithoutDuplicateIgnoreNew<T>::empty() const
{
	return count == 0;
}

template<typename T>
inline bool DequeWithoutDuplicateIgnoreNew<T>::full() const
{
	return count == N;
}

template<typename T>
inline void DequeWithoutDuplicateIgnoreNew<T>::clear()
{
	head = N;
	tail = 0;
}

template<typename T>
inline void DequeWithoutDuplicateIgnoreNew<T>::put_begin(T item)
{
	for (size_t i = head; i != tail;)
	{
		if (data[i] == item)
			return;

		++i;
		i = i % N;
	}

	if (full())
	{
		std::cout << "deque is full!\n";
		return;
	}

	head = head % N;

	if (empty())
	{
		data[head] = item;

		++tail;
	}
	else
	{
		if (head == 0)
			head = N - 1;
		else
			--head;

		data[head] = item;
	}

	++count;
}

template<typename T>
inline void DequeWithoutDuplicateIgnoreNew<T>::put_end(T item)
{
	for (size_t i = head % N; i != tail;)
	{
		if (data[i] == item)
			return;

		++i;
		i = i % N;
	}

	if (full())
	{
		std::cout << "deque is full!\n";
		return;
	}

	data[tail++] = item;
	tail = tail % N;

	++count;
}

template<typename T>
inline T DequeWithoutDuplicateIgnoreNew<T>::get_begin()
{
	if (empty())
		throw std::out_of_range("deque is empty\n");

	head = head % N;

	--count;

	return data[head++];
}

template<typename T>
inline T DequeWithoutDuplicateIgnoreNew<T>::get_end()
{
	if (empty())
		throw std::out_of_range("deque is empty\n");

	if (tail == 0)
		tail = N - 1;
	else
		--tail;

	auto val = data[tail];

	--count;

	return val;
}

template <typename T>
class DequeWithoutDuplicateDeleteOld
{
public:
	DequeWithoutDuplicateDeleteOld(size_t maxN) : data(new T[maxN + 1]), N(maxN), head(N), tail(0), count(0) {}
	~DequeWithoutDuplicateDeleteOld()
	{
		delete[] data;
	}

	bool empty() const;
	bool full() const;
	void clear();

	void put_begin(T item);
	void put_end(T item);

	T get_begin();
	T get_end();
private:
	T *data;
	size_t N, head, tail, count;

	void error(const std::string &msg) const;
	void chech_new_item(T item);
};

template<typename T>
inline bool DequeWithoutDuplicateDeleteOld<T>::empty() const
{
	return count == 0;
}

template<typename T>
inline bool DequeWithoutDuplicateDeleteOld<T>::full() const
{
	return count == N;
}

template<typename T>
inline void DequeWithoutDuplicateDeleteOld<T>::clear()
{
	head = N;
	tail = 0;
}

template<typename T>
inline void DequeWithoutDuplicateDeleteOld<T>::put_begin(T item)
{
	if (item >= N)
		error("calling 'push' out of range");

	chech_new_item(item);

	if (full())
	{
		std::cout << "deque is full!\n";
		return;
	}

	head = head % N;

	if (empty())
	{
		data[head] = item;

		++tail;
	}
	else
	{
		if (head == 0)
			head = N - 1;
		else
			--head;

		data[head] = item;
	}

	++count;
}

template<typename T>
inline void DequeWithoutDuplicateDeleteOld<T>::put_end(T item)
{
	if (item >= N)
		error("calling 'push' out of range");

	chech_new_item(item);

	if (full())
	{
		std::cout << "deque is full!\n";
		return;
	}

	data[tail++] = item;
	tail = tail % N;

	++count;
}

template<typename T>
inline T DequeWithoutDuplicateDeleteOld<T>::get_begin()
{
	if (empty())
		throw std::out_of_range("deque is empty\n");

	head = head % N;

	--count;

	return data[head++];
}

template<typename T>
inline T DequeWithoutDuplicateDeleteOld<T>::get_end()
{
	if (empty())
		throw std::out_of_range("deque is empty\n");

	if (tail == 0)
		tail = N - 1;
	else
		--tail;

	auto val = data[tail];

	--count;

	return val;
}

template<typename T>
inline void DequeWithoutDuplicateDeleteOld<T>::error(const std::string &msg) const
{
	throw std::out_of_range(msg);
}

template<typename T>
inline void DequeWithoutDuplicateDeleteOld<T>::chech_new_item(T item)
{
	size_t i = head % N;

	while (i != tail)
	{
		if (data[i] == item)
		{
			while (i != tail)
			{
				data[i] = data[(i + 1) % N];

				++i;
				i = i % N;
			}

			if (tail == 0)
				tail = N - 1;
			else
				--tail;

			--count;

			break;
		}

		++i;
		i = i % N;
	}
}

template <typename T>
class DequeUnordered
{
public:
	DequeUnordered(size_t maxN) : data(new T[maxN + 1]), N(maxN), head(N), tail(0), count(0) {}
	~DequeUnordered()
	{
		delete[] data;
	}

	bool empty() const;
	bool full() const;
	void clear();

	void put(T item);

	T get();
private:
	T *data;
	size_t N, head, tail, count;
};

template<typename T>
inline bool DequeUnordered<T>::empty() const
{
	return count == 0;
}

template<typename T>
inline bool DequeUnordered<T>::full() const
{
	return count == N;
}

template<typename T>
inline void DequeUnordered<T>::clear()
{
	head = N;
	tail = 0;
}

template<typename T>
inline void DequeUnordered<T>::put(T item)
{
	if (full())
	{
		std::cout << "deque is full!\n";
		return;
	}

	data[tail++] = item;
	tail = tail % N;

	++count;
}

template<typename T>
inline T DequeUnordered<T>::get()
{
	if (empty())
		throw std::out_of_range("deque is empty\n");

	head = head % N;

	if (count != 1)
	{
		size_t pos = head + rand() % (count - 1);

		if (pos != head)
			std::swap(data[head], data[pos]);
	}

	--count;

	return data[head++];
}

template <typename T>
class DequeList
{
private:
	struct node
	{
		node() : next(nullptr), prev(nullptr) {}
		node(T x) : item(x) {}
		node(std::shared_ptr<node> n, std::shared_ptr<node>p, T x) : next(n), prev(p), item(x) {}

		T item;
		std::shared_ptr<node> next;
		std::shared_ptr<node> prev;
	};
public:
	DequeList() : head(), tail() {}

	bool empty() const;
	bool full() const;
	void clear();

	void put_begin(T item);
	void put_end(T item);

	T get_begin();
	T get_end();
private:
	std::shared_ptr<node> head, tail;
};

template<typename T>
inline bool DequeList<T>::empty() const
{
	return !head;
}

template<typename T>
inline bool DequeList<T>::full() const
{
	return false;
}

template<typename T>
inline void DequeList<T>::clear()
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
inline void DequeList<T>::put_begin(T item)
{
	if (empty())
	{
		head = tail = std::make_shared<node>(item);
	}
	else
	{
		head = std::make_shared<node>(head, nullptr, item);
		head->next->prev = head;
	}
}

template<typename T>
inline void DequeList<T>::put_end(T item)
{	
	if (empty())
	{
		head = tail = std::make_shared<node>(item);
	}
	else
	{
		tail = std::make_shared<node>(nullptr, tail, item);
		tail->prev->next = tail;
	}
}

template<typename T>
inline T DequeList<T>::get_begin()
{
	auto val = head->item;

	head = head->next;
	
	if(head)
		head->prev = nullptr;

	return val;
}

template<typename T>
inline T DequeList<T>::get_end()
{
	auto val = tail->item;

	if (tail == head)
	{
		head = tail = nullptr;
	}
	else
	{
		tail = tail->prev;

		if (tail)
			tail->next = nullptr;
	}

	return val;
}

template <typename T>
class DequeListWithoutDuplicateIgnoreNew
{
private:
	struct node
	{
		node() : next(nullptr), prev(nullptr) {}
		node(T x) : item(x) {}
		node(std::shared_ptr<node> n, std::shared_ptr<node>p, T x) : next(n), prev(p), item(x) {}

		T item;
		std::shared_ptr<node> next;
		std::shared_ptr<node> prev;
	};
public:
	DequeListWithoutDuplicateIgnoreNew() : head(), tail() {}

	bool empty() const;
	bool full() const;
	void clear();

	void put_begin(T item);
	void put_end(T item);

	T get_begin();
	T get_end();
private:
	std::shared_ptr<node> head, tail;

	bool chech_new_item(T item);
};

template<typename T>
inline bool DequeListWithoutDuplicateIgnoreNew<T>::empty() const
{
	return !head;
}

template<typename T>
inline bool DequeListWithoutDuplicateIgnoreNew<T>::full() const
{
	return false;
}

template<typename T>
inline void DequeListWithoutDuplicateIgnoreNew<T>::clear()
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
inline void DequeListWithoutDuplicateIgnoreNew<T>::put_begin(T item)
{
	if (empty())
	{
		head = tail = std::make_shared<node>(item);
	}
	else
	{
		if (!chech_new_item(item))
			return;

		head = std::make_shared<node>(head, nullptr, item);
		head->next->prev = head;
	}
}

template<typename T>
inline void DequeListWithoutDuplicateIgnoreNew<T>::put_end(T item)
{
	if (empty())
	{
		head = tail = std::make_shared<node>(item);
	}
	else
	{
		if (!chech_new_item(item))
			return;

		tail = std::make_shared<node>(nullptr, tail, item);
		tail->prev->next = tail;
	}
}

template<typename T>
inline T DequeListWithoutDuplicateIgnoreNew<T>::get_begin()
{
	auto val = head->item;

	head = head->next;

	if (head)
		head->prev = nullptr;

	return val;
}

template<typename T>
inline T DequeListWithoutDuplicateIgnoreNew<T>::get_end()
{
	auto val = tail->item;

	if (tail == head)
	{
		head = tail = nullptr;
	}
	else
	{
		tail = tail->prev;

		if (tail)
			tail->next = nullptr;
	}

	return val;
}

template<typename T>
inline bool DequeListWithoutDuplicateIgnoreNew<T>::chech_new_item(T item)
{
	auto ptr = head;
	while (ptr)
	{
		if (ptr->item == item)
			return false;

		ptr = ptr->next;
	}

	return true;
}

template <typename T>
class DequeListWithoutDuplicateDeleteOld
{
private:
	struct node
	{
		node() : next(nullptr), prev(nullptr) {}
		node(T x) : item(x) {}
		node(std::shared_ptr<node> n, std::shared_ptr<node>p, T x) : next(n), prev(p), item(x) {}

		T item;
		std::shared_ptr<node> next;
		std::shared_ptr<node> prev;
	};
public:
	DequeListWithoutDuplicateDeleteOld() : head(), tail() {}

	bool empty() const;
	bool full() const;
	void clear();

	void put_begin(T item);
	void put_end(T item);

	T get_begin();
	T get_end();
private:
	std::shared_ptr<node> head, tail;

	bool chech_new_item(T item);
};

template<typename T>
inline bool DequeListWithoutDuplicateDeleteOld<T>::empty() const
{
	return !head;
}

template<typename T>
inline bool DequeListWithoutDuplicateDeleteOld<T>::full() const
{
	return false;
}

template<typename T>
inline void DequeListWithoutDuplicateDeleteOld<T>::clear()
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
inline void DequeListWithoutDuplicateDeleteOld<T>::put_begin(T item)
{
	if (empty())
	{
		head = tail = std::make_shared<node>(item);
	}
	else
	{
		if (!chech_new_item(item))
		{
			if (tail->item == item)
				tail = tail->prev;
		}

		head = std::make_shared<node>(head, nullptr, item);
		head->next->prev = head;

		if (!tail)
			tail = head;
	}
}

template<typename T>
inline void DequeListWithoutDuplicateDeleteOld<T>::put_end(T item)
{
	if (empty())
	{
		head = tail = std::make_shared<node>(item);
	}
	else
	{
		if (!chech_new_item(item))
		{
			if (head->item == item)
				head = head->next;
		}

		tail = std::make_shared<node>(nullptr, tail, item);
		tail->prev->next = tail;

		if (!head)
			head = tail;
	}
}

template<typename T>
inline T DequeListWithoutDuplicateDeleteOld<T>::get_begin()
{
	auto val = head->item;

	head = head->next;

	if (head)
		head->prev = nullptr;

	return val;
}

template<typename T>
inline T DequeListWithoutDuplicateDeleteOld<T>::get_end()
{
	auto val = tail->item;

	if (tail == head)
	{
		head = tail = nullptr;
	}
	else
	{
		tail = tail->prev;

		if (tail)
			tail->next = nullptr;
	}

	return val;
}

template<typename T>
inline bool DequeListWithoutDuplicateDeleteOld<T>::chech_new_item(T item)
{
	auto ptr = head;

	while (ptr && ptr->item != item)
	{
		ptr = ptr->next;
	}

	if (ptr)
	{
		auto prev = ptr->prev;
		auto next = ptr->next;

		if(prev)
			prev->next = next;
		if(next)
			next->prev = prev;

		return false;
	}

	return true;
}

template <typename T>
class DequeListUnordered
{
private:
	struct node
	{
		node() : next(nullptr) {}
		node(T x) : item(x) {}
		node(std::shared_ptr<node> n, T x) : next(n), item(x) {}

		T item;
		std::shared_ptr<node> next;
	};
public:
	DequeListUnordered() : head(), tail(), count(0) {}

	bool empty() const;
	bool full() const;
	void clear();

	void put(T item);

	T get();
private:
	std::shared_ptr<node> head, tail;
	size_t count;
};

template<typename T>
inline bool DequeListUnordered<T>::empty() const
{
	return !head;
}

template<typename T>
inline bool DequeListUnordered<T>::full() const
{
	return false;
}

template<typename T>
inline void DequeListUnordered<T>::clear()
{
	head = nullptr;
	tail = nullptr;
}

template<typename T>
inline void DequeListUnordered<T>::put(T item)
{
	if (empty())
	{
		head = tail = std::make_shared<node>(item);
	}
	else
	{
		tail->next = std::make_shared<node>(tail->next, item);
		tail = tail->next;
	}
	
	++count;
}

template<typename T>
inline T DequeListUnordered<T>::get()
{
	T val;

	if (head == tail)
	{
		val = head->item;

		head = tail = nullptr;
	}
	else
	{
		size_t pos = rand() % count;

		auto t = head;

		if (pos)
		{
			for (size_t i = 0; i < pos - 1; ++i)
				t = t->next;
		}

		val = t->next->item;

		if (tail == t->next)
		{
			tail = t->next->next;

			if (!tail)
				tail = t;
		}

		t->next = t->next->next;
	}

	--count;

	return val;
}

#endif
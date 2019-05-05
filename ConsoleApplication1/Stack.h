#ifndef STACK_H
#define STACK_H

#include <numeric>
#include <math.h>
#include <vector>
#include <string>

template <typename T>
class Stack
{
public:
	Stack(size_t maxN) : maxSize(maxN), data(new T[maxN]), N(0) {}
	Stack(const Stack<T> &rhs);

	Stack<T> & operator=(const Stack<T> &rhs);

	~Stack()
	{
		delete[] data;
	}

	bool empty() const;
	T back() const;
	size_t size() const;

	void push(T item);
	T pop();
private:
	T *data;
	size_t N, maxSize;

	void error(const std::string &msg) const;
};

template<typename T>
inline Stack<T>::Stack(const Stack<T>& rhs) : data(new T[rhs.maxSize]), N(rhs.N), maxSize(rhs.maxSize)
{
	for (size_t i = 0; i != N; ++i)
	{
		data[i] = rhs.data[i];
	}
}

template<typename T>
inline Stack<T>& Stack<T>::operator=(const Stack<T>& rhs)
{
	delete[] data;

	data = new T[rhs.maxSize];
	N = rhs.N;
	maxSize = rhs.maxSize;

	for (size_t i = 0; i != N; ++i)
	{
		data[i] = rhs.data[i];
	}

	return *this;
}

template<typename T>
inline bool Stack<T>::empty() const
{
	return N == 0;
}

template<typename T>
inline T Stack<T>::back() const
{
	if (empty())
	{
		error("calling 'back' at empty stack");
	}

	return data[N - 1];
}

template<typename T>
inline size_t Stack<T>::size() const
{
	return N;
}

template<typename T>
inline void Stack<T>::push(T item)
{
	if (N == maxSize)
	{
		error("calling 'push' at full stack");
	}

	data[N++] = item;
}

template<typename T>
inline T Stack<T>::pop()
{
	if (empty())
	{
		error("calling 'pop' at empty stack");
	}

	return data[--N];
}

template<typename T>
inline void Stack<T>::error(const std::string &msg) const
{
	throw std::out_of_range(msg);
}

template <typename T>
class StackWithoutDuplicate
{
public:
	StackWithoutDuplicate(size_t maxN) : maxSize(maxN), data(new T[maxN]), t(new T[maxN]), N(0) {}
	~StackWithoutDuplicate()
	{
		delete[] data;
		delete[] t;
	}

	bool empty() const;
	T back() const;
	size_t size() const;

	void push(T item);
	T pop();
private:
	T *data, *t;
	size_t N, maxSize;

	void error(const std::string &msg) const;
};

template<typename T>
inline bool StackWithoutDuplicate<T>::empty() const
{
	return N == 0;
}

template<typename T>
inline T StackWithoutDuplicate<T>::back() const
{
	if (empty())
	{
		error("calling 'back' at empty stack");
	}

	return data[N - 1];
}

template<typename T>
inline size_t StackWithoutDuplicate<T>::size() const
{
	return N;
}

template<typename T>
inline void StackWithoutDuplicate<T>::push(T item)
{
	if(item >= maxSize)
		error("calling 'push' out of range");

	if (t[item] == 1)
		return;

	if (N == maxSize)
	{
		error("calling 'push' at full stack");
	}

	data[N++] = item;
	t[item] = 1;
}

template<typename T>
inline T StackWithoutDuplicate<T>::pop()
{
	if (empty())
	{
		error("calling 'pop' at empty stack");
	}

	t[data[--N]] = 0;

	return data[N];
}

template<typename T>
inline void StackWithoutDuplicate<T>::error(const std::string &msg) const
{
	throw std::out_of_range(msg);
}

template <typename T>
class StackWithoutDuplicateIgnoreNew
{
public:
	StackWithoutDuplicateIgnoreNew(size_t maxN) : maxSize(maxN), data(new T[maxN]), N(0) {}
	~StackWithoutDuplicateIgnoreNew()
	{
		delete[] data;
	}

	bool empty() const;
	T back() const;
	size_t size() const;

	void push(T item);
	T pop();
private:
	T *data;
	size_t N, maxSize;

	void error(const std::string &msg) const;
};

template<typename T>
inline bool StackWithoutDuplicateIgnoreNew<T>::empty() const
{
	return N == 0;
}

template<typename T>
inline T StackWithoutDuplicateIgnoreNew<T>::back() const
{
	if (empty())
	{
		error("calling 'back' at empty stack");
	}

	return data[N - 1];
}

template<typename T>
inline size_t StackWithoutDuplicateIgnoreNew<T>::size() const
{
	return N;
}

template<typename T>
inline void StackWithoutDuplicateIgnoreNew<T>::push(T item)
{
	if (item >= maxSize)
		error("calling 'push' out of range");

	for (size_t i = 0; i != N; ++i)
	{
		if (data[i] == item)
			return;
	}

	if (N == maxSize)
	{
		error("calling 'push' at full stack");
	}

	data[N++] = item;
}

template<typename T>
inline T StackWithoutDuplicateIgnoreNew<T>::pop()
{
	if (empty())
	{
		error("calling 'pop' at empty stack");
	}

	return data[--N];
}

template<typename T>
inline void StackWithoutDuplicateIgnoreNew<T>::error(const std::string &msg) const
{
	throw std::out_of_range(msg);
}

template <typename T>
class StackWithoutDuplicateDeleteOld
{
public:
	StackWithoutDuplicateDeleteOld(size_t maxN) : maxSize(maxN), data(new T[maxN]), N(0) {}
	~StackWithoutDuplicateDeleteOld()
	{
		delete[] data;
	}

	bool empty() const;
	T back() const;
	size_t size() const;

	void push(T item);
	T pop();
private:
	T *data;
	size_t N, maxSize;

	void error(const std::string &msg) const;
};

template<typename T>
inline bool StackWithoutDuplicateDeleteOld<T>::empty() const
{
	return N == 0;
}

template<typename T>
inline T StackWithoutDuplicateDeleteOld<T>::back() const
{
	if (empty())
	{
		error("calling 'back' at empty stack");
	}

	return data[N - 1];
}

template<typename T>
inline size_t StackWithoutDuplicateDeleteOld<T>::size() const
{
	return N;
}

template<typename T>
inline void StackWithoutDuplicateDeleteOld<T>::push(T item)
{
	if (item >= maxSize)
		error("calling 'push' out of range");

	size_t i = 0;

	while(i < N && data[i] != item)
	{
		++i;
	}

	if (i < N)
	{
		for (; i < N; ++i)
		{
			data[i] = data[i + 1];
		}

		--N;
	}

	if (N == maxSize)
	{
		error("calling 'push' at full stack");
	}

	data[N++] = item;
}

template<typename T>
inline T StackWithoutDuplicateDeleteOld<T>::pop()
{
	if (empty())
	{
		error("calling 'pop' at empty stack");
	}

	return data[--N];
}

template<typename T>
inline void StackWithoutDuplicateDeleteOld<T>::error(const std::string &msg) const
{
	throw std::out_of_range(msg);
}

template <typename T>
class StackList
{
private:
	struct node
	{
		node() : next(nullptr) {}
		node(T x, std::shared_ptr<node> t = nullptr) : item(x), next(t) {}

		T item;
		std::shared_ptr<node> next;
	};
public:
	StackList(size_t maxN) : maxSize(maxN), head(nullptr), N(0) {}
	StackList(const StackList &rhs);

	StackList<T> & operator=(const StackList<T> &rhs);

	bool empty() const;
	T back() const;
	size_t size() const;

	void push(T item);
	T pop();
private:
	std::shared_ptr<node> head;
	size_t N, maxSize;

	void error(const std::string &msg) const;
};

template<typename T>
inline StackList<T>::StackList(const StackList & rhs) : N(rhs.N), maxSize(rhs.maxSize)
{
	auto ptr = rhs.head;

	while (ptr)
	{
		if (!head)
			head = std::make_shared<node>(ptr->item, nullptr);
		else
			head->next = std::make_shared<node>(ptr->item);

		ptr = ptr->next;
	}
}

template<typename T>
inline StackList<T> & StackList<T>::operator=(const StackList<T> & rhs)
{
	if (this == &rhs)
		return *this;

	N = rhs.N;
	maxSize = rhs.maxSize;

	auto ptr = rhs.head;

	while (ptr)
	{
		if (!head)
			head = std::make_shared<node>(ptr->item, nullptr);
		else
			head->next = std::make_shared<node>(ptr->item);

		ptr = ptr->next;
	}

	return *this;
}

template<typename T>
inline bool StackList<T>::empty() const
{
	return N == 0;
}

template<typename T>
inline T StackList<T>::back() const
{
	if (empty())
	{
		error("calling 'back' at empty stack");
	}

	return head->item;
}

template<typename T>
inline size_t StackList<T>::size() const
{
	return N;
}

template<typename T>
inline void StackList<T>::push(T item)
{
	if (N == maxSize)
	{
		error("calling 'push' at full stack");
	}

	head = std::make_shared<node>(item, head);

	++N;
}

template<typename T>
inline T StackList<T>::pop()
{
	if (empty())
	{
		error("calling 'pop' at empty stack");
	}

	auto val = head->item;

	head = head->next;

	--N;

	return val;
}

template<typename T>
inline void StackList<T>::error(const std::string &msg) const
{
	throw std::out_of_range(msg);
}

template <typename T>
class StackListWithoutDuplicateIgnoreNew
{
private:
	struct node
	{
		node() : next(nullptr) {}
		node(T x, std::shared_ptr<node> t = nullptr) : item(x), next(t) {}

		T item;
		std::shared_ptr<node> next;
	};
public:
	StackListWithoutDuplicateIgnoreNew(size_t maxN) : maxSize(maxN), head(nullptr), N(0) {}

	bool empty() const;
	T back() const;
	size_t size() const;

	void push(T item);
	T pop();
private:
	std::shared_ptr<node> head;
	size_t N, maxSize;

	void error(const std::string &msg) const;
};

template<typename T>
inline bool StackListWithoutDuplicateIgnoreNew<T>::empty() const
{
	return N == 0;
}

template<typename T>
inline T StackListWithoutDuplicateIgnoreNew<T>::back() const
{
	if (empty())
	{
		error("calling 'back' at empty stack");
	}

	return head->item;
}

template<typename T>
inline size_t StackListWithoutDuplicateIgnoreNew<T>::size() const
{
	return N;
}

template<typename T>
inline void StackListWithoutDuplicateIgnoreNew<T>::push(T item)
{
	auto ptr = head;
	while (ptr)
	{
		if (ptr->item == item)
			return;
		
		ptr = ptr->next;
	}

	if (N == maxSize)
	{
		error("calling 'push' at full stack");
	}

	head = std::make_shared<node>(item, head);

	++N;
}

template<typename T>
inline T StackListWithoutDuplicateIgnoreNew<T>::pop()
{
	if (empty())
	{
		error("calling 'pop' at empty stack");
	}

	auto val = head->item;

	head = head->next;

	--N;

	return val;
}

template<typename T>
inline void StackListWithoutDuplicateIgnoreNew<T>::error(const std::string &msg) const
{
	throw std::out_of_range(msg);
}

template <typename T>
class StackListWithoutDuplicateDeleteOld
{
private:
	struct node
	{
		node() : next(nullptr) {}
		node(T x, std::shared_ptr<node> t = nullptr) : item(x), next(t) {}

		T item;
		std::shared_ptr<node> next;
	};
public:
	StackListWithoutDuplicateDeleteOld(size_t maxN) : maxSize(maxN), head(nullptr), N(0) {}

	bool empty() const;
	T back() const;
	size_t size() const;

	void push(T item);
	T pop();
private:
	std::shared_ptr<node> head;
	size_t N, maxSize;

	void error(const std::string &msg) const;
};

template<typename T>
inline bool StackListWithoutDuplicateDeleteOld<T>::empty() const
{
	return N == 0;
}

template<typename T>
inline T StackListWithoutDuplicateDeleteOld<T>::back() const
{
	if (empty())
	{
		error("calling 'back' at empty stack");
	}

	return head->item;
}

template<typename T>
inline size_t StackListWithoutDuplicateDeleteOld<T>::size() const
{
	return N;
}

template<typename T>
inline void StackListWithoutDuplicateDeleteOld<T>::push(T item)
{
	auto ptr = head;

	if (!empty())
	{
		auto last_ptr = ptr;

		while (ptr && ptr->item != item)
		{
			last_ptr = ptr;

			ptr = ptr->next;
		}

		if (ptr)
		{
			last_ptr->next = ptr->next;

			--N;
		}
	}

	if (N == maxSize)
	{
		error("calling 'push' at full stack");
	}

	head = std::make_shared<node>(item, head);

	++N;
}

template<typename T>
inline T StackListWithoutDuplicateDeleteOld<T>::pop()
{
	if (empty())
	{
		error("calling 'pop' at empty stack");
	}

	auto val = head->item;

	head = head->next;

	--N;

	return val;
}

template<typename T>
inline void StackListWithoutDuplicateDeleteOld<T>::error(const std::string &msg) const
{
	throw std::out_of_range(msg);
}

template <typename T>
class StackDoubleLinkedWithoutDuplicateDeleteOld
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
	StackDoubleLinkedWithoutDuplicateDeleteOld(size_t maxN) : t(new std::shared_ptr<node>[maxN]), N(0), maxSize(maxN) {}
	~StackDoubleLinkedWithoutDuplicateDeleteOld()
	{
		delete[] t;
	}

	bool empty() const;
	T back() const;
	size_t size() const;

	void push(T item);
	T pop();
private:
	std::shared_ptr<node> head;
	std::shared_ptr<node> *t;
	size_t N, maxSize;

	void error(const std::string &msg) const;
};

template<typename T>
inline bool StackDoubleLinkedWithoutDuplicateDeleteOld<T>::empty() const
{
	return N == 0;
}

template<typename T>
inline T StackDoubleLinkedWithoutDuplicateDeleteOld<T>::back() const
{
	if (empty())
	{
		error("calling 'back' at empty stack");
	}

	return head->item;
}

template<typename T>
inline size_t StackDoubleLinkedWithoutDuplicateDeleteOld<T>::size() const
{
	return N;
}

template<typename T>
inline void StackDoubleLinkedWithoutDuplicateDeleteOld<T>::push(T item)
{
	if (t[item])
	{
		auto ptr = t[item];

		auto next = ptr->next;
		auto prev = ptr->prev;

		prev->next = ptr->next;
		next->prev = ptr->prev;

		t[item] = nullptr;
		--N;
	}

	if (N == maxSize)
	{
		error("calling 'push' at full stack");
	}

	if (empty())
	{
		head = std::make_shared<node>(nullptr, nullptr, item);
	}
	else
	{
		head = std::make_shared<node>(head, nullptr, item);
		head->next->prev = head;
	}

	t[item] = head;

	++N;
}

template<typename T>
inline T StackDoubleLinkedWithoutDuplicateDeleteOld<T>::pop()
{
	if (empty())
	{
		error("calling 'pop' at empty stack");
	}

	auto val = head->item;

	t[head->item] = nullptr;

	head = head->next;
	
	if(head)
		head->prev = nullptr;

	--N;

	return val;
}

template<typename T>
inline void StackDoubleLinkedWithoutDuplicateDeleteOld<T>::error(const std::string &msg) const
{
	throw std::out_of_range(msg);
}

#endif
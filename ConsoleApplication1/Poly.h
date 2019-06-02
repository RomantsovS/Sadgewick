#ifndef Poly_H
#define Poly_H

#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;

template <typename T> class Poly;

template <typename T> Poly<T> operator+(const Poly<T> &lhs, const Poly<T> &rhs);
template <typename T> Poly<T> operator-(const Poly<T> &lhs, const Poly<T> &rhs);
template <typename T> Poly<T> operator*(const Poly<T> &lhs, const Poly<T> &rhs);
template <typename T> Poly<T> operator/(const Poly<T> &lhs, const Poly<T> &rhs);
template <typename T> std::ostream & operator<<(std::ostream &os, const Poly<T> &p);

template <typename T>
class Poly
{
	friend Poly<T> operator+<T>(const Poly<T> &lhs, const Poly<T> &rhs);
	friend Poly<T> operator-<T>(const Poly<T> &lhs, const Poly<T> &rhs);
	friend Poly<T> operator*<T>(const Poly<T> &lhs, const Poly<T> &rhs);
	friend Poly<T> operator/<T>(const Poly<T> &lhs, const Poly<T> &rhs);
	friend std::ostream & operator<<<T>(std::ostream &os, const Poly<T> &p);
private:
	std::vector<T> data;
public:
	Poly(T c, double N)
	{
		if (N == 0 || N >= 1)
		{
			size_t n = static_cast<size_t>(N);

			data = std::vector<T>(n + 1);

			data[n] = c;

			for (size_t i = 0; i != n; ++i)
				data[i] = 0;
		}
		else
		{
			data = std::vector<T>(1);
			data[0] = 1;

			size_t n = static_cast<size_t>(1.0 / N);
		}
	}

	Poly(const Poly<T> &rhs) : data(rhs.data)
	{
	}

	Poly<T> & operator+=(const Poly<T> &rhs);
	Poly<T> & operator-=(const Poly<T> &rhs);
	Poly<T> & operator*=(const Poly<T> &rhs);
	Poly<T> & operator/=(const Poly<T> &rhs);

	double eval(float x) const
	{
		double t = 0.0;

		for (int i = data.size() - 1; i >= 0; --i)
		{
			t = t * x + data[i];
		}

		return t;
	}

	Poly<T> diff() const;
	Poly<T> integr() const;
};

template <typename T>
Poly<T> & Poly<T>::operator+=(const Poly<T> &rhs)
{
	if (rhs.data.size() > data.size())
	{
		data.resize(rhs.data.size());
	}

	for (size_t i = 0; i != rhs.data.size(); ++i)
		data[i] += rhs.data[i];

	return *this;
}

template<typename T>
inline Poly<T>& Poly<T>::operator-=(const Poly<T>& rhs)
{
	if (rhs.data.size() > data.size())
	{
		data.resize(rhs.data.size());
	}

	for (size_t i = 0; i != rhs.data.size(); ++i)
		data[i] -= rhs.data[i];

	return *this;
}

template<typename T>
inline Poly<T>& Poly<T>::operator*=(const Poly<T>& rhs)
{
	if (this == &rhs)
	{
		auto data_copy = data;

		for (auto &val : data)
			val = 0;

		data.resize(data_copy.size() + data_copy.size() - 1);

		for (size_t i = 0; i != data_copy.size(); ++i)
			for (size_t j = 0; j != data_copy.size(); ++j)
				data[i + j] += data_copy[i] * data_copy[j];

		return *this;
	}

	auto data_copy = data;

	for (auto &val : data)
		val = 0;

	data.resize(data.size() + rhs.data.size() - 1);

	for (size_t i = 0; i != data_copy.size(); ++i)
		for (size_t j = 0; j != rhs.data.size(); ++j)
			data[i + j] += data_copy[i] * rhs.data[j];

	return *this;
}

template<typename T>
inline Poly<T>& Poly<T>::operator/=(const Poly<T>& rhs)
{
	if (this == &rhs)
	{
		data.resize(1);
		data[0] = 1;

		return *this;
	}

	auto cur_dividend = *this;

	data.resize(data.size() - rhs.data.size() + 1);

	for (auto &val : data)
		val = 0;

	while (cur_dividend.data.size() >= rhs.data.size())
	{
		auto cur_divider = rhs;
		cur_divider.data.resize(cur_dividend.data.size());

		auto cur_coef = cur_dividend.data[cur_dividend.data.size() - 1];

		int size_dif = cur_dividend.data.size() - rhs.data.size();

		for (int i = cur_dividend.data.size() - 1; i >= size_dif; --i)
		{
			cur_divider.data[i] = cur_divider.data[i - size_dif] * cur_coef;
		}

		for (int i = size_dif - 1; i >= 0; --i)
		{
			cur_divider.data[i] = 0;
		}

		size_t index_res_data = cur_dividend.data.size() - rhs.data.size();
		data[index_res_data--] = cur_coef;

		cur_dividend = cur_dividend - cur_divider;

		if (cur_dividend.data[cur_dividend.data.size() - 1] == 0)
			cur_dividend.data.resize(cur_dividend.data.size() - 1);
	}

	return *this;
}

template<typename T>
inline Poly<T> Poly<T>::diff() const
{
	Poly<T> res(0, data.size() - 1);

	for (size_t i = data.size() - 1; i > 0; --i)
	{
		res.data[i - 1] = i * data[i];
	}

	return res;
}

template<typename T>
inline Poly<T> Poly<T>::integr() const
{
	Poly<T> res(0, data.size());

	for (int i = data.size() - 1; i >= 0; --i)
	{
		if (i > 0)
			res.data[i + 1] = data[i] / i;
		else
			res.data[i + 1] = data[i];
	}

	return res;
}

template <typename T>
Poly<T> operator+(const Poly<T> &lhs, const Poly<T> &rhs)
{
	Poly<T> t(lhs);

	t += rhs;

	return t;
}

template <typename T>
inline Poly<T> operator-<T>(const Poly<T>& lhs, const Poly<T>& rhs)
{
	Poly<T> t(lhs);

	t -= rhs;

	return t;
}

template <typename T>
Poly<T> operator*(const Poly<T> &lhs, const Poly<T> &rhs)
{
	Poly<T> t(lhs);

	t *= rhs;

	return t;
}

template <typename T>
inline Poly<T> operator/<T>(const Poly<T>& lhs, const Poly<T>& rhs)
{
	Poly<T> t(lhs);

	t /= rhs;

	return t;
}

template <typename T>
inline std::ostream & operator<<(std::ostream & os, const Poly<T> & p)
{
	bool first = true;

	for (size_t i = p.data.size() - 1; i > 0; --i)
	{
		if (p.data[i])
		{
			if (!first && p.data[i] > 0)
			{
				os << '+';
			}
			else
				first = false;

			os << p.data[i] << 'x' << '^' << i;
		}
	}

	if (p.data[0])
	{
		if (p.data.size() > 1 && p.data[0] > 0)
			os << '+';

		os << p.data[0];
	}

	return os;
}

///////////////////////////////////////////////////////////////////////////////////////////PolyList

template <typename T> class PolyList;

template <typename T> PolyList<T> operator+(const PolyList<T> &lhs, const PolyList<T> &rhs);
template <typename T> PolyList<T> operator*(const PolyList<T> &lhs, const PolyList<T> &rhs);
template <typename T> PolyList<T> operator/(const PolyList<T> &lhs, const PolyList<T> &rhs);
template <typename T> std::ostream & operator<<(std::ostream &os, const PolyList<T> &p);

template <typename T>
class PolyList
{
	struct node
	{
		node() : next(nullptr) {}
		node(T x, size_t index, std::shared_ptr<node> n = nullptr) : item(x), _index(index), next(n) {}

		T item;
		size_t _index;
		std::shared_ptr<node> next;
	};

	friend PolyList<T> operator+<T>(const PolyList<T> &lhs, const PolyList<T> &rhs);
	friend PolyList<T> operator*<T>(const PolyList<T> &lhs, const PolyList<T> &rhs);
	friend PolyList<T> operator/<T>(const PolyList<T> &lhs, const PolyList<T> &rhs);
	friend std::ostream & operator<<<T>(std::ostream &os, const PolyList<T> &p);
private:
	std::shared_ptr<node> head;
public:
	PolyList() : head(nullptr) {}

	PolyList(T c, size_t N)
	{
		head = std::make_shared<node>(c, N, nullptr);
	}

	PolyList(const PolyList<T> &rhs)
	{
		auto ptr = rhs.head;

		decltype(head) last_head = nullptr;

		while (ptr)
		{
			if (!last_head)
			{
				head = std::make_shared<node>(ptr->item, ptr->_index, head);
				last_head = head;
			}
			else
			{
				auto t = std::make_shared<PolyList<T>::node>(ptr->item, ptr->_index);
				last_head = last_head->next = t;
			}

			ptr = ptr->next;
		}
	}

	PolyList<T> & operator+=(const PolyList<T> &rhs);
	PolyList<T> & operator*=(const PolyList<T> &rhs);
	PolyList<T> & operator/=(const PolyList<T> &rhs);

	double eval(float x) const
	{
		double t = 0.0;

		auto ptr = head;

		int last_Index = ptr->_index;

		while (ptr)
		{
			int cur_index = ptr->_index;

			while (last_Index > cur_index)
			{
				t = t * x;
				--last_Index;
			}

			t = t + ptr->item;

			last_Index = cur_index;

			ptr = ptr->next;
		}

		while (last_Index > 0)
		{
			t = t * x;

			--last_Index;
		}

		return t;
	}

	PolyList<T> diff() const;
	PolyList<T> integr() const;
};

template <typename T>
PolyList<T> operator+(const PolyList<T> &lhs, const PolyList<T> &rhs)
{
	PolyList<T> t(lhs);

	t += rhs;

	return t;
}

template <typename T>
PolyList<T> operator*(const PolyList<T> &lhs, const PolyList<T> &rhs)
{
	PolyList<T> t(lhs);

	t *= rhs;

	return t;
}

template <typename T>
PolyList<T> operator/<T>(const PolyList<T>& lhs, const PolyList<T>& rhs)
{
	PolyList<T> t(lhs);

	t /= rhs;

	return t;
}

template <typename T>
inline std::ostream & operator<<(std::ostream & os, const PolyList<T> & p)
{
	auto ptr = p.head;

	bool first = true;

	while (ptr)
	{
		if (!first && ptr->item > 0)
		{
			os << '+';
		}
		else
			first = false;

		if (ptr->_index)
			os << ptr->item << 'x' << '^' << ptr->_index;
		else
			os << ptr->item;

		ptr = ptr->next;
	}

	return os;
}

template<typename T>
inline PolyList<T>& PolyList<T>::operator+=(const PolyList<T>& rhs)
{
	if (!rhs.head)
	{
		return *this;
	}

	auto ptr = rhs.head;

	auto cur_ptr_res = head;

	decltype(head) last_head = nullptr;

	while (ptr)
	{
		if (cur_ptr_res && ptr->_index == cur_ptr_res->_index)
		{
			cur_ptr_res->item += ptr->item;
			last_head = cur_ptr_res;

			ptr = ptr->next;
		}
		else if (cur_ptr_res && ptr->_index > cur_ptr_res->_index)
		{
			if (!last_head)
			{
				head = std::make_shared<PolyList<T>::node>(ptr->item, ptr->_index, cur_ptr_res);
				last_head = head;
			}
			else
			{
				auto t = std::make_shared<PolyList<T>::node>(ptr->item, ptr->_index, cur_ptr_res);
				last_head->next = t;

				last_head = t;
			}

			ptr = ptr->next;
		}
		else if (!cur_ptr_res)
		{
			auto t = std::make_shared<PolyList<T>::node>(ptr->item, ptr->_index, cur_ptr_res);

			cur_ptr_res = t;

			if (last_head)
				last_head->next = t;
			else
				last_head = head = t;

			ptr = ptr->next;
		}
		else
		{
			last_head = cur_ptr_res;
			cur_ptr_res = cur_ptr_res->next;
		}
	}

	return *this;
}

template<typename T>
inline PolyList<T>& PolyList<T>::operator*=(const PolyList<T>& rhs)
{
	PolyList<T> copy(*this);

	if (this == &rhs)
	{
		head = nullptr;

		auto cur_ptr_l = copy.head;

		while (cur_ptr_l)
		{
			auto cur_ptr_r = copy.head;

			while (cur_ptr_r)
			{
				auto index = cur_ptr_l->_index + cur_ptr_r->_index;
				auto item = cur_ptr_l->item * cur_ptr_r->item;

				auto cur_ptr_res = std::make_shared<PolyList<T>::node>(item, index, nullptr);
				PolyList<T> p;
				p.head = cur_ptr_res;

				*this = *this + p;

				cur_ptr_r = cur_ptr_r->next;
			}

			cur_ptr_l = cur_ptr_l->next;
		}

		return *this;
	}

	head = nullptr;

	auto cur_ptr_l = copy.head;

	while (cur_ptr_l)
	{
		auto cur_ptr_r = rhs.head;

		while (cur_ptr_r)
		{
			auto index = cur_ptr_l->_index + cur_ptr_r->_index;
			auto item = cur_ptr_l->item * cur_ptr_r->item;

			auto cur_ptr_res = std::make_shared<PolyList<T>::node>(item, index, nullptr);
			PolyList<T> p;
			p.head = cur_ptr_res;

			*this = *this + p;

			cur_ptr_r = cur_ptr_r->next;
		}

		cur_ptr_l = cur_ptr_l->next;
	}

	return *this;
}

template<typename T>
inline PolyList<T>& PolyList<T>::operator/=(const PolyList<T>& rhs)
{
	if (this == &rhs)
	{
		head = std::make_shared<PolyList<T>::node>(1, 0);

		return *this;
	}

	auto cur_dividend = *this;

	head = nullptr;

	while (cur_dividend.head._index >= rhs.head->_index)
	{
		auto cur_divider = rhs;

		auto cur_coef = cur_dividend.head->item;

		int size_dif = cur_dividend.head->_index - rhs.head->_index;

		auto ptr = cur_dividend.head;

		while(ptr)
		{
			ptr->item = ptr->item * cur_coef;
			ptr->index += size_dif;

			ptr = ptr->next;
		}

		auto index = cur_dividend.head->_index - rhs.head->_index;
		auto cur_ptr_res = std::make_shared<PolyList<T>::node>(cur_coef, index, nullptr);
		PolyList<T> p;
		p.head = cur_ptr_res;

		*this = *this + p;

		cur_dividend = cur_dividend - cur_divider;
	}

	return *this;
}

template<typename T>
inline PolyList<T> PolyList<T>::diff() const
{
	PolyList<T> res;

	auto ptr = head;

	auto last_head = res.head;

	while (ptr)
	{
		if (ptr->_index > 1)
		{
			if (!last_head)
			{
				last_head = res.head = std::make_shared<PolyList<T>::node>(ptr->item * ptr->_index, ptr->_index - 1);
			}
			else
			{
				auto t = std::make_shared<PolyList<T>::node>(ptr->item * ptr->_index, ptr->_index - 1);

				last_head->next = t;
			}
		}

		ptr = ptr->next;
	}

	return res;
}

template<typename T>
inline PolyList<T> PolyList<T>::integr() const
{
	PolyList<T> res;

	auto ptr = head;

	auto last_head = res.head;

	while (ptr)
	{
		auto index = ptr->_index == 0 ? 1 : ptr->_index;

		if (!last_head)
		{
			last_head = res.head = std::make_shared<PolyList<T>::node>(ptr->item / index, ptr->_index + 1);
		}
		else
		{
			auto t = std::make_shared<PolyList<T>::node>(ptr->item / index, ptr->_index + 1);

			last_head = last_head->next = t;
		}

		ptr = ptr->next;
	}

	return res;
}

#endif
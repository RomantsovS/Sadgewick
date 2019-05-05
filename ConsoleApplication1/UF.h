#ifndef UF_H
#define UF_H

#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;

class uf
{
public:
	virtual bool find(size_t p, size_t q) const = 0;
	virtual void unite(size_t p, size_t q) = 0;

	virtual void print() const = 0;

	virtual size_t num_unioned_nodes(size_t p) const = 0;
};

class UF : public uf
{
private:
	std::vector<size_t> id, sz;

	size_t find_root(size_t x) const
	{
		while (x != id[x])
		{
			x = id[x];
		}

		return x;
	}

public:
	UF(size_t N) : id(N), sz(N)
	{
		for (size_t i = 0; i != N; ++i)
		{
			id[i] = i;
			sz[i] = 1;
		}
	}

	bool find(size_t p, size_t q) const override
	{
		return find_root(p) == find_root(q);
	}

	void unite(size_t p, size_t q) override
	{
		size_t i, j;
		
		for (i = p; i != id[i]; i = id[i])
		{
			id[i] = id[id[i]];
		}
		for (j = q; j != id[j]; j = id[j])
		{
			id[j] = id[id[j]];
		}

		if (i == j)
			return;

		if (sz[i] < sz[j])
		{
			id[i] = j;
			sz[j] += sz[i];
		}
		else
		{
			id[j] = i;
			sz[i] += sz[j];
		}
	}

	void print() const override
	{
		for (const auto val : id)
			cout << val << " ";

		cout << endl;
	}

	size_t num_unioned_nodes(size_t p) const override
	{
		auto p_root = find_root(p);

		size_t res = 0;

		for(size_t i = 0; i != id.size(); ++i)
		{
			if (i == p)
				continue;

			if (p_root == find_root(i))
				++res;
		}

		return res;
	}
};

class UFstruct : public uf
{
private:
	struct str
	{
		size_t id, sz;
	};

	std::vector<str> data;

	size_t find_root(size_t x) const
	{
		while (x != data[x].id)
		{
			x = data[x].id;
		}

		return x;
	}

public:
	UFstruct(size_t N) : data(N)
	{
		for (size_t i = 0; i != N; ++i)
		{
			data[i].id = i;
			data[i].sz = 1;
		}
	}

	bool find(size_t p, size_t q) const override
	{
		return find_root(p) == find_root(q);
	}

	void unite(size_t p, size_t q) override
	{
		size_t i, j;

		for (i = p; i != data[i].id; i = data[i].id)
		{
			data[i].id = data[data[i].id].id;
		}
		for (j = q; j != data[j].id; j = data[j].id)
		{
			data[j].id = data[data[j].id].id;
		}

		if (i == j)
			return;

		if (data[i].sz < data[j].sz)
		{
			data[i].id = j;
			data[j].sz += data[i].sz;
		}
		else
		{
			data[j].id = i;
			data[i].sz += data[j].sz;
		}
	}

	void print() const override
	{
		for (const auto val : data)
			cout << val.id << " ";

		cout << endl;
	}

	size_t num_unioned_nodes(size_t p) const override
	{
		auto p_root = find_root(p);

		size_t res = 0;

		for (size_t i = 0; i != data.size(); ++i)
		{
			if (i == p)
				continue;

			if (p_root == find_root(i))
				++res;
		}

		return res;
	}
};

#endif
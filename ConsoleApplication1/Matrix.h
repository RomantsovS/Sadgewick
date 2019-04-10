#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

using std::cout;
using std::endl;

template<typename T>
T **malloc2d(int r, int c)
{
	auto **t = new T *[r];
	for (int i = 0; i < r; ++i)
	{
		t[i] = new T[c];
		memset(t[i], 0, sizeof(int) * c);
	}

	return t;
}

template<typename T>
T ***malloc3d(int r, int c, int b)
{
	auto ***t = new T **[r];
	for (int i = 0; i < r; ++i)
	{
		t[i] = malloc2d<T>(c, b);
	}

	memset(t, 0, sizeof(int) * r * c * b);

	return t;
}

template<typename T>
void print_mat2d(T** mat2d, size_t r, size_t c)
{
	for (size_t i = 0; i != r; ++i)
	{
		for (size_t j = 0; j != c; ++j)
			std::cout << mat2d[i][j] << " ";
		std::cout << endl;
	}
}

template<typename T> class Matrix2d;

template<typename T> Matrix2d<T> operator*(const Matrix2d<T> &l, const Matrix2d<T> &r);

template<typename T>
class Matrix2d
{
	friend Matrix2d<T> operator*(const Matrix2d<T> &l, const Matrix2d<T> &r);
public:
	Matrix2d(size_t r, size_t c) : num_rows(r), num_cols(c), data(r)
	{
		for (auto &row : data)
		{
			row.resize(c);
		}
	}

	Matrix2d(size_t r, size_t c, T val) : Matrix2d(r, c)
	{
		for (auto &row : data)
			for (auto &col : row)
				col = val;
	}

	void print() const
	{
		for (auto &row : data)
		{
			for (auto &col : row)
				cout << col << " ";
			cout << endl;
		}
	}
private:
	size_t num_rows, num_cols;
	std::vector<std::vector<T>> data;
};

template<typename T>
Matrix2d<T> operator*(const Matrix2d<T> &l, const Matrix2d<T> &r)
{
	if (l.num_cols != r.num_rows)
		throw std::invalid_argument("Num cols of left matrix != num rows of right!\n");

	Matrix2d<T> res(l.num_rows, r.num_cols, 0);

	for (size_t i = 0; i != l.num_rows; ++i)
	{
		for (size_t j = 0; j != l.num_cols; ++j)
		{
			res.data[i][j] += l.data[i][j] * r.data[j][i];
		}
	}

	return res;
}

template<typename T> class multilist_mat2d;

template<typename T> multilist_mat2d<T> operator*(const multilist_mat2d<T> &l, const multilist_mat2d<T> &r);

template<typename T>
class multilist_mat2d
{
private:
	template<typename T>
	struct node_multi_dimension
	{
		node_multi_dimension(T x) : item(x), dimensions(2, nullptr) {}

		T item;
		std::vector<std::shared_ptr<node_multi_dimension<T>>> dimensions;
	};

	using sp_nmd = std::shared_ptr<node_multi_dimension<T>>;

	std::vector<sp_nmd> rows;
	std::vector<sp_nmd> cols;

	void print_list_multi_dimension(const sp_nmd start, size_t index) const
	{
		auto t = start;

		while (t != nullptr)
		{
			cout << t->item << " ";
			t = t->dimensions[index];
		}
	}

	friend multilist_mat2d<T> operator*(const multilist_mat2d<T> &l, const multilist_mat2d<T> &r);
public:
	multilist_mat2d(size_t r, size_t c) : rows(r, nullptr), cols(c, nullptr) {}
	multilist_mat2d(T **mat, size_t r, size_t c) : rows(r, nullptr), cols(c, nullptr)
	{
		for (size_t i = 0; i != r; ++i)
		{
			auto &cur_rows_ptr = rows[i];

			for (size_t j = 0; j != c; ++j)
			{
				auto & cur_cols_ptr = cols[j];

				if (mat[i][j])
				{
					auto node = std::make_shared<node_multi_dimension<T>>(mat[i][j]);

					if (!cur_rows_ptr)
						cur_rows_ptr = node;
					else
					{
						auto cur_rows_ptr_tmp = cur_rows_ptr.get();

						while (cur_rows_ptr_tmp->dimensions[0])
							cur_rows_ptr_tmp = cur_rows_ptr_tmp->dimensions[0].get();

						cur_rows_ptr_tmp->dimensions[0] = node;
					}

					if (!cur_cols_ptr)
						cur_cols_ptr = node;
					else
					{
						auto cur_cols_ptr_tmp = cur_cols_ptr.get();

						while (cur_cols_ptr_tmp->dimensions[1])
							cur_cols_ptr_tmp = cur_cols_ptr_tmp->dimensions[1].get();

						cur_cols_ptr_tmp->dimensions[1] = node;
					}
				}
			}
		}
	}

	void print() const
	{
		for (auto row_iter = rows.begin(); row_iter != rows.end(); ++row_iter)
		{
			if (*row_iter)
			{
				auto cur_row_node = *row_iter;

				for (auto col_iter = cols.begin(); col_iter != cols.end(); ++col_iter)
				{
					if (cur_row_node)
					{
						auto cur_col_node = *col_iter;

						while (cur_col_node && cur_col_node != cur_row_node)
							cur_col_node = cur_col_node->dimensions[1];

						if (cur_row_node == cur_col_node)
						{
							cout << cur_row_node->item;

							cur_row_node = cur_row_node->dimensions[0];
						}
						else
						{
							cout << 0;
						}
					}
					else
					{
						cout << 0;
					}

					cout << " ";
				}
			}
			else
			{
				for (size_t i = 0; i != cols.size(); ++i)
					cout << 0 << " ";
			}

			cout << endl;
		}
	}
};

template<typename T>
multilist_mat2d<T> operator*(const multilist_mat2d<T> &l, const multilist_mat2d<T> &r)
{
	if (l.cols.size() != r.rows.size())
		throw std::invalid_argument("Num cols of left matrix != num wors of right!\n");

	multilist_mat2d<T> res(l.rows.size(), r.cols.size());

	for (auto row_iter = l.rows.begin(); row_iter != l.rows.end(); ++row_iter)
	{
		if (*row_iter)
		{
			auto cur_row_node = *row_iter;

			for (auto col_iter = l.cols.begin(); col_iter != l.cols.end(); ++col_iter)
			{
				if (cur_row_node)
				{
					auto cur_col_node = *col_iter;

					while (cur_col_node && cur_col_node != cur_row_node)
						cur_col_node = cur_col_node->dimensions[1];

					if (cur_row_node == cur_col_node)
					{
						cout << cur_row_node->item;

						cur_row_node = cur_row_node->dimensions[0];
					}
					else
					{
						cout << 0;
					}
				}
				else
				{
					cout << 0;
				}

				cout << " ";
			}
		}
		else
		{
			for (size_t i = 0; i != l.cols.size(); ++i)
				cout << 0 << " ";
		}

		cout << endl;
	}
}

#endif
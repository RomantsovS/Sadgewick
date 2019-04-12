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
	friend Matrix2d<T> operator*<T>(const Matrix2d<T> &l, const Matrix2d<T> &r);
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

	size_t num_rows, num_cols;
	std::vector<std::vector<T>> data;
};

template<typename T>
Matrix2d<T> operator*(const Matrix2d<T> &l, const Matrix2d<T> &r)
{
	if (l.num_cols != r.num_rows)
		throw std::invalid_argument("Num cols of left matrix != num rows of right!\n");

	Matrix2d<T> res(l.num_rows, r.num_cols, 0);

	for (size_t i = 0; i != res.num_rows; ++i)
	{
		for (size_t j = 0; j != res.num_cols; ++j)
		{
			for (size_t ii = 0; ii != l.num_cols; ++ii)
			{
				res.data[i][j] += l.data[i][ii] * r.data[ii][j];
			}
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

	friend multilist_mat2d<T> operator*<T>(const multilist_mat2d<T> &l, const multilist_mat2d<T> &r);
public:
	multilist_mat2d(size_t r, size_t c) : rows(r, nullptr), cols(c, nullptr) {}
	
	multilist_mat2d(T **mat2d_ptr, size_t r, size_t c) : rows(r, nullptr), cols(c, nullptr)
	{
		fill_data(mat2d_ptr);
	}

	multilist_mat2d(const Matrix2d<T> &mat2d) : rows(mat2d.num_rows, nullptr), cols(mat2d.num_cols, nullptr)
	{
		fill_data(mat2d.data);
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
private:
	template <typename Ty>
	void fill_data(Ty mat)
	{
		for (size_t i = 0; i != rows.size(); ++i)
		{
			auto &cur_rows_ptr = rows[i];

			for (size_t j = 0; j != cols.size(); ++j)
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
};

template<typename T>
multilist_mat2d<T> operator*(const multilist_mat2d<T> &l, const multilist_mat2d<T> &r)
{
	if (l.cols.size() != r.rows.size())
		throw std::invalid_argument("Num cols of left matrix != num rows of right!\n");

	multilist_mat2d<T> res(l.rows.size(), r.cols.size());

	for (size_t i = 0; i != res.rows.size(); ++i)
	{
		if (!l.rows[i])
			continue;

		auto cur_rows_node = res.rows[i].get();
		auto cur_l_rows_node = l.rows[i].get();

		for (size_t j = 0; j != res.cols.size(); ++j)
		{
			if (!r.cols[j])
				continue;

			auto cur_cols_node = res.cols[j].get();
			auto cur_r_cols_node = r.cols[j].get();

			T res_val = 0;

			for (size_t ii = 0; ii != l.cols.size(); ++i)
			{
				auto cur_l_cols_node = l.cols[ii];

				while (cur_l_rows_node)
				{
					T left_val = 0;

					for (auto &cur_l_cols_ptr : l.cols)
					{
						if (cur_l_rows_node)
						{
							auto cur_l_col_node = *cur_l_cols_ptr;

							while (cur_l_col_node && cur_l_col_node.get() != cur_l_rows_node)
								cur_l_col_node = cur_l_col_node->dimensions[1].get();

							if (cur_l_col_node == cur_l_rows_node)
							{
								left_val = cur_l_col_node->item;
								cur_l_rows_node = cur_l_rows_node->dimensions[0].get();
							}
						}
					}

					if (!left_val)
						continue;

					T right_val = 0;

					for (auto &cur_r_rows_ptr : r.rows)
					{
						if (cur_r_cols_node)
						{
							while (cur_r_rows_ptr && cur_r_rows_ptr.get() != cur_r_cols_node)
								cur_r_rows_ptr = cur_r_rows_ptr->dimensions[1];

							if (cur_r_rows_ptr.get() == cur_r_cols_node)
							{
								right_val = cur_r_rows_ptr->item;
								cur_r_cols_node = cur_r_cols_node->dimensions[1].get();
							}
						}
					}

					if (right_val)
						res_val += left_val * right_val;
				}

				if (res_val)
				{
					auto node = std::make_shared<multilist_mat2d<T>::node_multi_dimension<T>>(res_val);

					if (!cur_rows_node)
					{
						res.rows[i] = node;
						cur_rows_node = node.get();
					}
					else
					{
						node->dimensions[0] = cur_rows_node->dimensions[0];
						cur_rows_node = node.get();
					}

					if (!cur_cols_node)
					{
						res.cols[i] = node;
						cur_cols_node = node.get();
					}
					else
					{
						node->dimensions[1] = cur_cols_node->dimensions[1];
						cur_cols_node = node.get();
					}
				}
			}
		}
	}

	return res;
}

#endif
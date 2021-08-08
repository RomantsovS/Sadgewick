#ifndef SORT_H_
#define SORT_H_

#include "../Mas.h"

extern const size_t N;
extern const char min_num, max_num;

template<typename T>
void compexch(T &A, T &B) {
	if(B < A)
		std::swap(A, B);
}

template <typename T>
void bubble_sort(std::vector<T> &mas, size_t speed)
{
	bool sorted = false;

	for (size_t i = 0; i != mas.size(); ++i)
	{
		sorted = true;
		for (size_t j = mas.size() - 1; j > i; --j)
		{

			if (mas[j] < mas[j - 1])
			{
				std::swap(mas[j - 1], mas[j]);
				sorted = false;

				#if defined PRINT_SORT
				print_mas(max_num, min_num, mas, N, speed, "bubble_sort");
				#endif
			}
		}
		if(sorted)
			break;
	}
	
	#if defined PRINT_SORT
	print_mas(max_num, min_num, mas, N, speed, "bubble_sort");
	#endif
}

template <typename T>
void shaker_sort(vector<T> &mas, size_t speed)
{
	bool sorted = false;
	bool forward = false;
	
	size_t index = 0;

	for (size_t i = 0; i != mas.size() - 1; ++i)
	{
		sorted = true;

		if (forward)
		{
			for (size_t j = i + 1 - index; j < mas.size() - index; ++j)
			{
				if (mas[j] < mas[j - 1])
				{
					std::swap(mas[j], mas[j - 1]);
					sorted = false;

					#if defined PRINT_SORT
					print_mas(max_num, min_num, mas, N, speed, "shaker_sort");
					#endif
				}
			}
			++index;
		}
		else
		{
			for (size_t j = mas.size() - 1 - i + index; j > i - index; --j)
			{
				if (mas[j] < mas[j - 1])
				{
					std::swap(mas[j], mas[j - 1]);
					sorted = false;

					#if defined PRINT_SORT
					print_mas(max_num, min_num, mas, N, speed, "shaker_sort");
					#endif
				}
			}
		}
		if (sorted)
			break;

		forward = !forward;
	}

	#if defined PRINT_SORT
	print_mas(max_num, min_num, mas, N, speed, "shaker_sort");
	#endif
}

template <typename T>
void selection_sort(std::vector<T> &mas, size_t speed)
{
	for (size_t i = 0; i != mas.size(); ++i)
	{
		int min = mas[i];
		size_t minIndex = i;

		for (size_t j = i + 1; j != mas.size(); ++j)
		{
			if (mas[j] < min)
			{
				min = mas[j];
				minIndex = j;
			}
		}

		auto tmp = mas[i];
		mas[i] = min;
		mas[minIndex] = tmp;

		#if defined PRINT_SORT
		print_mas(max_num, min_num, mas, N, speed, "selection_sort");
		#endif
	}
}

template <typename T>
void insertion_sort(T mas[], int l, int r, size_t speed = 0)
{
	int j;
	T tmp;

	for (int i = l + 1; i != r + 1; ++i)
	{

		tmp = mas[i];
		j = i - 1;

		while(j >= 0 && mas[j] > tmp)
		{
			mas[j + 1] = mas[j];
			mas[j] = tmp;
			j--;

			#if defined PRINT_SORT
			print_mas(max_num, min_num, &mas[l], &mas[r], N, speed, "insertion_sort");
			#endif
		}

		#if defined PRINT_SORT
		print_mas(max_num, min_num, &mas[l], &mas[r], N, speed, "insertion_sort");
		#endif
	}
}

template <typename T>
void insertion_sort(std::vector<T> &mas, size_t speed) {
	insertion_sort(&mas[0], 0, mas.size() - 1, speed);
}

template <typename T>
void shall_sort(vector<T>& mas, size_t speed)
{
	size_t h;

	for (h = 1; h <= (mas.size() - 2) / 9; h = 3 * h + 1)
		;
	for (; h > 0; h /= 3)
		for (size_t i = h; i <= mas.size() - 1; ++i)
		{
			size_t j = i;
			auto v = mas[i];

			while (j >= h && v < mas[j - h])
			{
				mas[j] = mas[j - h];
				j -= h;

				#if defined PRINT_SORT
				print_mas(max_num, min_num, mas, N, speed, "shall_sort");
				#endif
			}

			mas[j] = v;

			#if defined PRINT_SORT
			print_mas(max_num, min_num, mas, N, speed, "shall_sort");
			#endif
		}
}

template <typename Item>
int partition(std::vector<Item> &a, int l, int r, size_t speed = 0)
{
	int i = l - 1, j = r;
	Item v = a[r];

	for (;;)
	{
		while (a[++i] < v)
			;
		while (v < a[--j])
			if (j == l)
				break;
		if (i >= j)
			break;

		std::swap(a[i], a[j]);

		#if defined PRINT_SORT
		print_mas(max_num, min_num, a, N, speed, "quick_sort");
		#endif
	}

	std::swap(a[i], a[r]);
	
	#if defined PRINT_SORT
	print_mas(max_num, min_num, &a[l], &a[r], N, speed, "quick_sort");
	#endif

	return i;
}

template <typename Item>
void quicksort(std::vector<Item> &a, int l, int r, size_t speed = 0)
{
	if (r <= l)
		return;

	int i = partition(a, l, r, speed);

	#if defined PRINT_SORT
	print_mas(max_num, min_num, &a[l], &a[r], N, speed, "quick_sort");
	#endif

	quicksort(a, l, i - 1, speed);
	quicksort(a, i + 1, r, speed);
}

template <typename Item>
void quick_sort(std::vector<Item> &a, size_t speed)
{
	quicksort(a, 0, a.size() -1, speed);
}

template <class Item>
void merge(Item a[], int l, int m, int r)
{
	int i, j;
	static Item aux[N];
	for (i = m + 1; i > l; i--)
		aux[i - 1] = a[i - 1];
	for (j = m; j < r; j++)
		aux[r + m - j] = a[j + 1];
	for (int k = l; k <= r; k++)
		if (aux[j] < aux[i])
			a[k] = aux[j--];
		else
			a[k] = aux[i++];
}

template <class Item>
void mergesort(Item a[], int l, int r, size_t speed = 0)
{
	if (r <= l)
		return;

	#if defined PRINT_SORT
	print_mas(max_num, min_num, &a[l], &a[r], N, speed, "merge_sort");
	#endif

	int m = (r + l) / 2;
	mergesort(a, l, m, speed);
	mergesort(a, m + 1, r, speed);
	merge(a, l, m, r);
}

template <typename Item>
void merge_sort(std::vector<Item> &a, size_t speed)
{
	mergesort(&a[0], 0, a.size() -1, speed);
}

#endif

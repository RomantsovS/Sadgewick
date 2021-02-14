#ifndef SORT_H_
#define SORT_H_

#include "../Mas.h"

extern const size_t N;
extern const char min_num, max_num;

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
void insertion_sort(std::vector<T> &mas, size_t speed)
{
	int j;
	T tmp;

	for (size_t i = 1; i != mas.size(); ++i)
	{

		tmp = mas[i];
		j = i - 1;

		while(j >= 0 && mas[j] > tmp)
		{
			mas[j + 1] = mas[j];
			mas[j] = tmp;
			j--;

			#if defined PRINT_SORT
			print_mas(max_num, min_num, mas, N, speed, "insertion_sort");
			#endif
		}

		#if defined PRINT_SORT
		print_mas(max_num, min_num, mas, N, speed, "insertion_sort");
		#endif
	}
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

template <typename T>
void quick_sort_ranged(T *beg, T *end, size_t speed)
{
	if (end - beg < 2)
		return;

	auto p = *(beg + (end - beg) / 2);

	int i = 0, temp;
	auto j = end - beg;

	while (i < j)
	{
		while (*(beg + i) < p)
		{
			++i;
		}

		while (*(beg + j) > p)
		{
			--j;
		}

		temp = *(beg + i);
		*(beg + i) = *(beg + j);
		*(beg + j) = temp;

		i++;
		j--;

		#if defined PRINT_SORT
		print_mas(max_num, min_num, beg, end, N, speed, "quick_sort_ranged");
		#endif
	}

	quick_sort_ranged(beg, beg + j, speed);
	quick_sort_ranged(beg + j + 1, end, speed);
}

template <typename T>
void quick_sort(std::vector<T> &mas, size_t speed)
{
	quick_sort_ranged(&mas.front(), &mas.back(), speed);
}

#endif
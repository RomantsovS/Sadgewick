#ifndef  SORT_H
#define SORT_H

#include<vector>

template <typename T>
void insertion_sort(std::vector<T>& mas)
{
	int j;
	T tmp;

	for (int i = 1; i != mas.size(); ++i)
	{
		tmp = mas[i];
		j = i - 1;

		while (j >= 0 && mas[j] > tmp)
		{
			mas[j + 1] = mas[j];
			mas[j] = tmp;
			j--;
		}
	}
}

#endif // ! SORT_H

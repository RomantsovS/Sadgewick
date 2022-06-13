#include <iostream>
#include <vector>

#include "../../../Mas.h"

using namespace std;

const int bitsword = 32;
const int bitsbyte = 1;
const int bytesword = bitsword / bitsbyte;
const int R = 1 << bitsbyte;

inline int digit(long A, int B) { return (A >> bitsbyte * (bytesword - B - 1)) & (R - 1); }

template <class Item>
void quicksortB(Item a[], int l, int r, int d) {
    int i = l, j = r;
    if (r <= l || d > bitsword) return;
    while (j != i) {
        while (digit(a[i], d) == 0 && (i < j)) i++;
        while (digit(a[j], d) == 1 && (j > i)) j--;
        swap(a[i], a[j]);
    }
    if (digit(a[r], d) == 0) j++;
    quicksortB(a, l, j - 1, d + 1);
    quicksortB(a, j, r, d + 1);
}

template <class Item>
void sort(Item a[], int l, int r) {
    quicksortB(a, l, r, 0);
}

int main() {
    // size_t n = 255;

    // for (size_t i = 0; i < 32; ++i) {
    //     cout << digit(n, i);
    // }

    int a[] = {8, 3, 1, 4};
    print_mas(a, a + 4);

    sort(a, 0, 3);

    print_mas(a, a + 4);

    return 0;
}
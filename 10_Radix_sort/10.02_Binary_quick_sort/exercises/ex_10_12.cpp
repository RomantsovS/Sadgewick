#include <algorithm>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

#include "../../../Mas.h"

using namespace std;

const int bitsword = sizeof(int) * 8;
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
void binsort(Item a[], int l, int r) {
    quicksortB(a, l, r, 0);
}

template <class Item>
void sort_10_12(Item a[], int l, int r) {
    size_t i = 0;
    for (; i < bitsword; ++i) {
        int v = digit(a[l], i);
        int j = l + 1;
        for (; j <= r; ++j) {
            if (digit(a[j], i) != v) break;
        }
        if (j <= r) break;
    }
    quicksortB(a, l, r, i);
}

template<typename F>
void f(F f, size_t N) {
    vector<int> ivec(N);
    for(size_t i = 0; i < N; ++i) {
        ivec[i] = rand() % (2 << 15);
    }

    if(N < 100)
        print_mas(ivec, 8);

    auto start = chrono::steady_clock::now();

    f(ivec.data(), 0, ivec.size() - 1);

    if(N < 100)
        print_mas(ivec, 8);

    auto end = chrono::steady_clock::now();

    cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms" << endl;
}

int main() {
    f(binsort<int>, 10);
    f(sort_10_12<int>, 10);
    
    f(binsort<int>, 10'000);
    f(binsort<int>, 100'000);
    f(binsort<int>, 1'000'000);
    f(binsort<int>, 10'000'000);

    f(sort_10_12<int>, 10'000);
    f(sort_10_12<int>, 100'000);
    f(sort_10_12<int>, 1'000'000);
    f(sort_10_12<int>, 10'000'000);

    return 0;
}
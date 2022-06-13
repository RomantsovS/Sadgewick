#include <iostream>
#include <vector>

#include "../../../Mas.h"
#include "../../../Sort/sort.h"

using namespace std;

const int bitsword = 32;
const int bitsbyte = 1;
const int bytesword = bitsword / bitsbyte;
const int R = 1 << bitsbyte;

inline int digit(long A, int B) { return (A >> bitsbyte * (bytesword - B - 1)) & (R - 1); }

const int M = 1;
const size_t maxN = 100;

#define bin(A) l + count[A]

template <class Item>
void radixMSD(Item a[], int l, int r, int d) {
    int i, j;
    vector<int> count(R + 1);
    static Item aux[maxN];
    if (d > bytesword) return;
    if (r - l <= M) {
        insertion_sort(a, l, r);
        return;
    }
    for (j = 0; j < R; j++) count[j] = 0;
    for (i = l; i <= r; i++) count[digit(a[i], d) + 1]++;
    for (j = 1; j < R; j++) count[j] += count[j - 1];
    for (i = l; i <= r; i++) aux[l + count[digit(a[i], d)]++] = a[i];
    for (i = l; i <= r; i++) a[i] = aux[i];
    radixMSD(a, l, bin(0) - 1, d + 1);
    for (j = 0; j < R - 1; j++) radixMSD(a, bin(j), bin(j + 1) - 1, d + 1);
}

int main() {
    size_t N = 10;
    vector<int> ivec(N);
    for (size_t i = 0; i < N; ++i) {
        ivec[i] = rand() % (2 << 3);
    }

    print_mas(ivec, 8);

    for (auto n : ivec) {
        for (size_t i = 0; i < bytesword; ++i) {
            cout << digit(n, i);
        }
        cout << endl;
    }

    radixMSD(ivec.data(), 0, ivec.size() - 4, 0);

    print_mas(ivec, 8);

    return 0;
}
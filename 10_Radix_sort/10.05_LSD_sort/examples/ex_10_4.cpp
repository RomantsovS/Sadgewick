#include <iostream>
#include <string>
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

template <class Item>
void radixLSD(Item a[], int l, int r) {
    static Item aux[maxN];
    for (int d = bytesword - 1; d >= 0; d--) {
        int i, j, count[R + 1];
        for (j = 0; j < R; j++) count[j] = 0;
        for (i = l; i <= r; i++) count[digit(a[i], d) + 1]++;
        for (j = 1; j < R; j++) count[j] += count[j - 1];
        for (i = l; i <= r; i++) aux[count[digit(a[i], d)]++] = a[i];
        for (i = l; i <= r; i++) a[i] = aux[i];
    }
}

int main() {
    size_t N = 10;
    vector<int> ivec(N);
    for (size_t i = 0; i < N; ++i) {
        ivec[i] += rand() % (1 << 7);
    }

    print_mas(ivec, 8);

    radixLSD(ivec.data(), 0, ivec.size() - 1);

    print_mas(ivec, 8);

    return 0;
}
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

// inline int digit(long A, int B) { return (A >> bitsbyte * (bytesword - B - 1)) & (R - 1); }
inline int digit(const string& A, int B) { return A[B]; }

const int M = 1;
const size_t maxN = 100;

#define ch(A) digit(A, d)

template <class Item>
void quicksortX(Item a[], int l, int r, int d) {
    int i, j, k, p, q;
    int v;
    if (r - l <= M) {
        insertion_sort(a, l, r);
        return;
    }
    v = ch(a[r]);
    i = l - 1;
    j = r;
    p = l - 1;
    q = r;
    while (i < j) {
        while (ch(a[++i]) < v)
            ;
        while (v < ch(a[--j]))
            if (j == l) break;
        if (i > j) break;
        swap(a[i], a[j]);
        if (ch(a[i]) == v) {
            p++;
            swap(a[p], a[i]);
        }
        if (v == ch(a[j])) {
            q--;
            swap(a[j], a[q]);
        }
    }
    if (p == q) {
        if (v != '\0') quicksortX(a, l, r, d + 1);
        return;
    }
    if (ch(a[i]) < v) i++;
    for (k = l; k <= p; k++, j--) swap(a[k], a[j]);
    for (k = r; k >= q; k--, i++) swap(a[k], a[i]);
    quicksortX(a, l, j, d);
    if ((i == r) && ch(a[i]) == v) i++;
    if (v != '\0') quicksortX(a, j + 1, i - 1, d + 1);
    quicksortX(a, i, r, d);
}

int main() {
    size_t N = 10;
    vector<string> ivec(N);
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            ivec[i] += 'A' + rand() % (3);
        }
    }

    print_mas(ivec, 8);

    quicksortX(ivec.data(), 0, ivec.size() - 1, 0);

    print_mas(ivec, 8);

    return 0;
}
#pragma once

#include <algorithm>

template <class Item>
void fixDown(Item a[], int k, int N) {
    while (2 * k <= N) {
        int j = 2 * k;
        if (j < N && a[j] < a[j + 1]) j++;
        if (!(a[k] < a[j])) break;
        std::swap(a[k], a[j]);
        k = j;
    }
}

template <class Item>
void heapsort(Item a[], int l, int r) {
    int k, N = r - l + 1;
    Item *pq = a + l - 1;
    for (k = N / 2; k >= 1; k--)
        fixDown(pq, k, N);
    while (N > 1) {
        std::swap(pq[1], pq[N]);
        fixDown(pq, 1, --N);
    }
}
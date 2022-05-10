#pragma once

#include <algorithm>

template <class Item>
void fixUp(Item a[], int k) {
    while (k > 1 && a[k / 2] < a[k]) {
        std::swap(a[k], a[k / 2]);
        k = k / 2;
    }
}

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
class PQ {
   private:
    Item *pq;
    int N;

   public:
    PQ(int maxN) {
        pq = new Item[maxN + 1];
        N = 0;
    }
    ~PQ() { delete[] pq; }
    int empty() const { return N == 0; }
    void insert(Item item) {
        pq[++N] = item;
        fixUp(pq, N);
    }
    Item getmax() {
        std::swap(pq[1], pq[N]);
        fixDown(pq, 1, N - 1);
        return pq[N--];
    }
};
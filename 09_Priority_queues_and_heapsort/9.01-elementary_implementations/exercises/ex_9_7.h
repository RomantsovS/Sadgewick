#pragma once

#include <algorithm>

template <class Item>
class PQOrderedArray {
   private:
    Item *pq;
    int N;

   public:
    PQOrderedArray(int maxN) {
        pq = new Item[maxN];
        N = 0;
    }
    ~PQOrderedArray() { delete[] pq; }
    int empty() const { return N == 0; }
    void insert(Item item) {
        size_t i = 0;
        while (i < N && pq[i] <= item) ++i;
        for (size_t j = N; j > i; --j) {
            pq[j] = pq[j - 1];
        }

        pq[i] = item;
        ++N;
    }
    Item getmax() { return pq[--N]; }
};
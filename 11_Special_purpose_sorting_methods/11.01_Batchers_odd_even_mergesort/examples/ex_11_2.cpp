#include <iostream>

#include "../../../Mas.h"

#include "shuffle_unshuffle.h"

using namespace std;

template <typename T>
void compexch(T &A, T &B) {
    if (B < A) std::swap(A, B);
}

template <class Item>
void merge(Item a[], int l, int m, int r) {
    if (r == l + 1) compexch(a[l], a[r]);
    if (r < l + 2) return;
    unshuffle(a, l, r);
    merge(a, l, (l + m) / 2, m);
    merge(a, m + 1, (m + 1 + r) / 2, r);
    shuffle(a, l, r);
    for (int i = l + 1; i < r; i += 2) compexch(a[i], a[i + 1]);
}

int main() {
    {
        size_t N = 8;
        vector<char> ivec = {'A', 'G', 'I', 'N', 'O', 'R', 'S', 'T',
        'A', 'E', 'E', 'L', 'M', 'P', 'X', 'Y'};

        print_mas(ivec, 4);

        merge(ivec.data(), 0, ivec.size() / 2 - 1, ivec.size() - 1);

        print_mas(ivec, 4);
    }

    return 0;
}
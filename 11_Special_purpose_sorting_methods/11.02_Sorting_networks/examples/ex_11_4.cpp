#include <iostream>

#include "../../../Mas.h"

using namespace std;

template <typename T>
void compexch(T &A, T &B) {
    if (B < A) std::swap(A, B);
}

template <class Item>
void batchersort(Item a[], int l, int r) {
    int N = r - l + 1;
    for (int p = 1; p < N; p += p)
        for (int k = p; k > 0; k /= 2)
            for (int j = k % p; j + k < N; j += (k + k))
                for (int i = 0; i < N - j - k; i++)
                    if ((j + i) / (p + p) == (j + i + k) / (p + p)) compexch(a[l + j + i], a[l + j + i + k]);
}

int main() {
    {
        vector<char> ivec = {'A', 'G', 'I', 'N', 'O', 'R', 'S', 'T', 'A', 'E', 'E', 'L', 'M', 'P', 'X', 'Y'};

        print_mas(ivec, 4);

        batchersort(ivec.data(), 0, ivec.size() - 1);

        print_mas(ivec, 4);
    }

    return 0;
}
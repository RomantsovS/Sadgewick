#include <iostream>

#include "../../../Mas.h"

using namespace std;

template <typename T>
void compexch(T &A, T &B) {
    if (B < A) std::swap(A, B);
}

template <class Item>
void merge(Item a[], int l, [[maybe_unused]] int m, int r) {
    int N = r - l + 1;  // предполагается, чага
    // N/2 это m-1+1
    for (int k = N / 2; k > 0; k /= 2)
        for (int j = k % (N / 2); j + k < N; j += k + k)
            for (int i = 0; i < k; i++) compexch(a[l + j + i], a[l + j + i + k]);
}

int main() {
    {
        vector<char> ivec = {'A', 'G', 'I', 'N', 'O', 'R', 'S', 'T',
        'A', 'E', 'E', 'L', 'M', 'P', 'X', 'Y'};

        print_mas(ivec, 4);

        merge(ivec.data(), 0, ivec.size() / 2 - 1, ivec.size() - 1);

        print_mas(ivec, 4);
    }

    return 0;
}
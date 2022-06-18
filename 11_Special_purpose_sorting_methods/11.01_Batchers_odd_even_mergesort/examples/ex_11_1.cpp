#include <iostream>

#include "../../../Mas.h"
#include "shuffle_unshuffle.h"


using namespace std;

int main() {
    {
        size_t N = 10;
        vector<int> ivec(N);
        for (size_t i = 0; i < N; ++i) {
            ivec[i] = rand() % 10;
        }

        print_mas(ivec, 8);

        shuffle(ivec.data(), 0, ivec.size() - 1);

        print_mas(ivec, 8);
    }

    {
        size_t N = 10;
        vector<int> ivec(N);
        for (size_t i = 0; i < N; ++i) {
            ivec[i] = rand() % 10;
        }

        print_mas(ivec, 8);

        unshuffle(ivec.data(), 0, ivec.size() - 1);

        print_mas(ivec, 8);
    }

    return 0;
}
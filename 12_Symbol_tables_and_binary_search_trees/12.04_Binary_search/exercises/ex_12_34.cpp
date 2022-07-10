#include <cassert>
#include <iostream>
#include <vector>

#include "../../../Mas.h"

using namespace std;

template <typename Item>
Item bin_search(vector<Item>& mas, size_t l, size_t r, Item v) {
    while (l < r) {
        size_t m = (l + r) / 2;
        if (v == mas[m])
            return m;
        else if (v < mas[v]) {
            r = m;
        } else {
            l = m;
        }
    }

    return -1;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    {
        vector<int> ivec = {1, 3, 5, 7, 9};

        assert(bin_search(ivec, 0, ivec.size(), 5) == 2);
        assert(bin_search(ivec, 0, ivec.size(), 2) == -1);
        assert(bin_search(ivec, 0, 0, 5) == -1);
    }

    {
        vector<int> ivec = {1, 3, 5, 7};

        assert(bin_search(ivec, 0, ivec.size(), 1) == 0);
        assert(bin_search(ivec, 0, ivec.size(), 3) == 1);
        assert(bin_search(ivec, 0, 0, 2) == -1);
    }

    cout << "ok\n";
}
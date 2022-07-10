#include <iostream>
#include <vector>

#include "../../../Mas.h"

using namespace std;

static const int maxKey = 10;

template <typename Item>
Item searchR(vector<Item>& mas, size_t l, size_t r, Item v) {
    size_t m = (l + r) / 2;
    if (v == mas[m]) return m;
    if (l == r) return -1;
    if (v < mas[m])
        return searchR(mas, l, m - 1, v);
    else
        return searchR(mas, m + 1, r, v);
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    vector<int> ivec = {1, 3, 5, 7, 9};

    print_mas(ivec);

    std::cout << searchR(ivec, 0, ivec.size(), 5) << endl;
    std::cout << searchR(ivec, 0, ivec.size(), 2) << endl;
}
#include "ex_9_7.h"

#include <cassert>
#include <iostream>
#include <vector>

#include "../../../Mas.h"

using namespace std;

int main() {
    {
        int a[] = {8, 3, 1, 4};
        print_mas(a, a + 4);

        heapsort(a, 0, 3);

        print_mas(a, a + 4);
    }
    {
        int a[] = {8, 3, 1, 4};
        vector v(begin(a), end(a));
        print_mas(v);

        heapsort(v.data(), 0, 3);

        print_mas(v);
    }

    return 0;
}
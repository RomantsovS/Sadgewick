#include <cassert>
#include <iostream>

#include "../../../Mas.h"
#include "ex_9_5.h"

using namespace std;

template <class Item>
void PQsort(Item a[], int l, int r) {
    int k;
    PQ<Item> pq(r - l + 1);
    for (k = l; k <= r; k++) pq.insert(a[k]);
    for (k = r; k >= l; k--) a[k] = pq.getmax();
}

int main() {
    int a[] = {8, 3, 1, 4};
    print_mas(a, a + 4);

    PQsort(a, 0, 3);

    print_mas(a, a + 4);

    return 0;
}
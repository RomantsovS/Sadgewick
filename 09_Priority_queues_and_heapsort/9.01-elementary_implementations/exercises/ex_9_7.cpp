#include <cassert>
#include <iostream>

#include "ex_9_7.h"

using namespace std;

int main() {
    {
        PQOrderedArray<int> pq(10);

        pq.insert(1);
        assert(!pq.empty());
        assert(pq.getmax() == 1);
        assert(pq.empty());
    }
    {
        PQOrderedArray<int> pq(10);

        pq.insert(1);
        pq.insert(10);
        pq.insert(3);
        pq.insert(5);

        assert(pq.getmax() == 10);
        assert(pq.getmax() == 5);
        assert(pq.getmax() == 3);
        assert(pq.getmax() == 1);
        assert(pq.empty());
    }

    cout << "ok\n";

    return 0;
}
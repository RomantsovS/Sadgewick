#include <cassert>
#include <iostream>
#include <chrono>

#include "../examples/ex_9_2.h"
#include "ex_9_8.h"

using namespace std;
using namespace chrono;

int main() {
    {
        size_t n = 1'000;

        PQ<int> pq(n);
        for(size_t i = 0; i < n; ++i) {
            pq.insert(rand() % 1'000);
        }

        size_t cnt = 0;

        auto start = steady_clock::now();

        while(duration_cast<milliseconds>(steady_clock::now() - start).count() < 1'000) {
            pq.getmax();
            pq.insert(rand() % 1'000);
            ++cnt;
        }
        cout << "cnt=" << cnt << endl;
    }
    {
        size_t n = 1'000;

        PQUnorderedList<int> pq;
        for(size_t i = 0; i < n; ++i) {
            pq.insert(rand() % 1'000);
        }

        size_t cnt = 0;

        auto start = steady_clock::now();

        while(duration_cast<milliseconds>(steady_clock::now() - start).count() < 1'000) {
            pq.getmax();
            pq.insert(rand() % 1'000);
            ++cnt;
        }
        cout << "cnt=" << cnt << endl;
    }

    return 0;
}
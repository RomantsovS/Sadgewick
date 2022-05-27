#include <tree.h>

#include <iostream>

using namespace std;

template <typename T>
using link = typename CTree<T>::node*;

template <typename T>
static link<T> pair_(link<T> p, link<T> q) {
    if (p->item < q->item) {
        p->r = q->l;
        q->l = p;
        return q;
    } else {
        q->r = p->l;
        p->l = q;
        return p;
    }
}

constexpr size_t maxBQsize = 3;
link<int> bq[maxBQsize];

template <typename T>
link<T> insert(T v) {
    auto t = new typename CTree<T>::node(v), c = t;
    for (int i = 0; i < maxBQsize; i++) {
        if (c == 0) break;
        if (bq[i] == 0) {
            bq[i] = c;
            break;
        }
        c = pair_<T>(c, bq[i]);
        bq[i] = 0;
    }
    return t;
}

int main() {
    for (int i = 0; i < 7; ++i) {
        insert(i);
        for (size_t j = 0; j < maxBQsize; ++j) {
            print<int>(bq[j]);
            cout << "====\n";
        }
        cout << "===============\n";
    }

    return 0;
}
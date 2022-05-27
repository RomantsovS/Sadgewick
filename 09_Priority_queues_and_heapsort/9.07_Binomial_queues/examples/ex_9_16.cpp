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

static inline int test(int C, int B, int A) { return 4 * C + 2 * B + 1 * A; }

template <typename T>
void BQjoin(link<T>* a, link<T>* b) {
    link<T> c = nullptr;
    for (int i = 0; i < maxBQsize; ++i) {
        switch (test(c != 0, b[i] != 0, a[i] != 0)) {
            case 2:
                a[i] = b[i];
                break;
            case 3:
                c = pair_<T>(a[i], b[i]);
                a[i] = 0;
                break;
            case 4:
                a[i] = c, c = 0;
                break;
            case 5:
                c = pair_<T>(c, a[i]);
                a[i] = 0;
                break;
            case 6:
            case 7:
                c = pair_<T>(c, b[i]);
                break;
        }
    }
}

template <typename Item>
Item getmax() {
    int i, max;
    Item v = 0;
    link<Item>* temp = new link<Item>[maxBQsize];
    for (i = 0, max = -1; i < maxBQsize; i++)
        if (bq[i] != 0)
            if ((max == -1) || (v < bq[i]->item)) {
                max = i;
                v = bq[max]->item;
            }
    link<Item> x = bq[max]->l;
    for (i = max; i < maxBQsize; i++) temp[i] = 0;
    for (i = max; i > 0; i--) {
        temp[i - 1] = x;
        x = x->r;
        temp[i - 1]->r = 0;
    }
    bq[max] = nullptr;
    BQjoin<Item>(bq, temp);
    delete[] temp;
    return v;
}

int main() {
    for (int i = 0; i < 7; ++i) {
        insert(i);
    }

    for (size_t j = 0; j < maxBQsize; ++j) {
        print<int>(bq[j]);
        cout << "===\n";
    }
    cout << "=================\n";

    cout << getmax<int>();

    return 0;
}
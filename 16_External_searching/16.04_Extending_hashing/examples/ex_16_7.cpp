#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const std::string red_str("\033[0;31m");
std::string reset_str("\033[0m");

const int bitsword = 8;
const int bitsbyte = 1;
const int bytesword = bitsword / bitsbyte;
const int R = 1 << bitsbyte;

inline int digit(long A, int B) { return (A >> bitsbyte * (bytesword - B - 1)) & (R - 1); }

using Key = int;
Key maxKey = 1000;

#include <Item.h>

int bits(Key key, int A, int B) {
    if (A == 0 && B == 0) return 0;

    int res = 0;

    for (int i = A; i < A + B; ++i) res += digit(key, i);
    return res;
}

const int M = 6;

template <class Item, class Key>
class ST {
   private:
    struct node {
        int m;
        Item b[M];
        int k;
        node() {
            m = 0;
            k = 0;
        }
    };
    typedef node *link;
    link *dir;
    Item nullItem;
    int N, d, D;

    Item search(link h, Key v) {
        for (int j = 0; j < h->m; j++)
            if (v == h->b[j].key()) return h->b[j];
        return nullItem;
    }

    void split(link h) {
        link t = new node;
        while (h->m == 0 || h->m == M) {
            h->m = t->m = 0;
            for (int j = 0; j < M; j++)
                if (bits(h->b[j].key(), h->k, 1) == 0)
                    h->b[h->m++] = h->b[j];
                else
                    t->b[t->m++] = h->b[j];
            t->k = ++h->k;
            insertDIR(t, t->k);
        }
    }

    void insert(link h, Item x) {
        int j;
        Key v = x.key();
        for (j = 0; j < h->m; j++)
            if (v < h->b[j].key()) break;
        for (int i = (h->m)++; i > j; i--) h->b[i] = h->b[i - 1];
        h->b[j] = x;
        if (h->m == M) split(h);
    }

    void insertDIR(link t, int k) {
        int i, m, x = bits(t->b[0].key(), 0, k);
        while (d < k) {
            link *old = dir;
            d += 1;
            D += D;
            dir = new link[D];
            for (i = 0; i < D; i++) dir[i] = old[i / 2];
            if (d < k) dir[bits(x, 0, d) ^ 1] = new node;
        }
        for (m = 1; k < d; k++) m *= 2;
        for (i = 0; i < m; i++) dir[x * m + i] = t;
    }

   public:
    ST() {
        N = 0;
        d = 0;
        D = 1;
        dir = new link[D];
        dir[0] = new node;
    }

    Item search(Key v) { return search(dir[bits(v, 0, d)], v); }

    void insert(Item x) { insert(dir[bits(x.key(), 0, d)], x); }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    ST<Item, Key> st;

    vector<int> svec = {0153, 0176, 0513, 0601, 0706, 0773, 0742, 0373};

    for (size_t i = 0; i < svec.size(); ++i) {
        std::cout << std::setw(4) << svec[i] << ": ";
        for (size_t j = 0; j < bytesword; ++j) {
            std::cout << digit(svec[i], j);
        }
        std::cout << endl;

        st.insert(svec[i]);

        for (size_t j = 0; j <= i; ++j) {
            assert(st.search(svec[i]).key() == svec[i]);
        }
    }

    assert(st.search(0).null());

    cout << "ok\n";
}
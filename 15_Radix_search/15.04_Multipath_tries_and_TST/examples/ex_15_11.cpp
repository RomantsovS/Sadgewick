#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

using Key = string;
Key maxKey = "";

#include <Item.h>

inline int digit(const string& A, int B) { return A[B] - 'A' + 1; }

int NULLdigit = -64;

template <class Item, class Key, size_t Num>
class TST {
   private:
    struct node {
        Item item;
        int d;
        node *l, *m, *r;
        node(Item x, int k) {
            item = x;
            d = k;
            l = 0;
            m = 0;
            r = 0;
        }
        node(node* h, int k) {
            d = k;
            l = 0;
            m = h;
            r = 0;
        }
        int internal() { return d != NULLdigit; }
    };
    typedef node* link;
    link heads[Num];
    Item nullItem;

    link split(link p, link q, int d) {
        int pd = digit(p->item.key(), d), qd = digit(q->item.key(), d);
        link t = new node(nullItem, qd);
        if (pd < qd) {
            t->m = q;
            t->l = new node(p, pd);
        }
        if (pd == qd) {
            t->m = split(p, q, d + 1);
        }
        if (pd > qd) {
            t->m = q;
            t->r = new node(p, pd);
        }
        return t;
    }
    link newext(Item x) { return new node(x, NULLdigit); }
    void insertR(link& h, Item x, int d) {
        int i = digit(x.key(), d);
        if (h == 0) {
            h = new node(newext(x), i);
            return;
        }
        if (!h->internal()) {
            h = split(newext(x), h, d);
            return;
        }
        if (i < h->d) insertR(h->l, x, d);
        if (i == h->d) insertR(h->m, x, d + 1);
        if (i > h->d) insertR(h->r, x, d);
    }

    Item searchR(link h, Key v, int d) {
        if (h == 0) return nullItem;
        if (h->internal()) {
            int i = digit(v, d), k = h->d;
            if (i < k) return searchR(h->l, v, d);
            if (i == k) return searchR(h->m, v, d + 1);
            if (i > k) return searchR(h->r, v, d);
        }
        if (v == h->item.key()) return h->item;
        return nullItem;
    }

   public:
    TST() {
        for (int i = 0; i < Num; i++) heads[i] = 0;
    }
    void insert(Item x) { insertR(heads[digit(x.key(), 0)], x, 1); }
    Item search(Key v) { return searchR(heads[digit(v, 0)], v, 1); }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    TST<Item, Key, 26> st;

    vector<string> svec = {"NOW", "IS", "THE", "FOR", "TIME", "THEORY"};

    for (size_t i = 0; i < svec.size(); ++i) {
        std::cout << std::setw(4) << svec[i] << ": ";
        for (size_t j = 0; j <= svec[i].size(); ++j) {
            std::cout << std::setw(3) << digit(svec[i], j) << ' ';
        }
        std::cout << endl;
        st.insert(svec[i]);

        for (size_t j = 0; j <= i; ++j) {
            assert(st.search(svec[i]).key() == svec[i]);
        }
    }

    assert(st.search("test").null());

    cout << "ok\n";
}
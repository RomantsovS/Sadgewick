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

template <class Item, class Key>
class TST {
    struct node {
        Item item;
        int d;
        node *l, *m, *r;
        node(int k) {
            d = k;
            l = 0;
            m = 0;
            r = 0;
        }
    };
    typedef node* link;
    link head;
    Item nullItem;

    Item searchR(link h, Key v, int d) {
        int i = digit(v, d);
        if (h == 0) return nullItem;
        if (i == NULLdigit) {
            Item dummy(v);
            return dummy;
        }
        if (i < h->d) return searchR(h->l, v, d);
        if (i == h->d) return searchR(h->m, v, d + 1);
        if (i > h->d) return searchR(h->r, v, d);

        return nullItem;
    }
    void insertR(link& h, Item x, int d) {
        int i = digit(x.key(), d);
        if (h == 0) h = new node(i);
        if (i == NULLdigit) return;
        if (i < h->d) insertR(h->l, x, d);
        if (i == h->d) insertR(h->m, x, d + 1);
        if (i > h->d) insertR(h->r, x, d);
    }

   public:
    TST() { head = 0; }
    Item search(Key v) { return searchR(head, v, 0); }
    void insert(Item x) { insertR(head, x, 0); }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    TST<Item, Key> st;

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
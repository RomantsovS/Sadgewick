#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

using Key = string;
Key maxKey = "";

#include <Item.h>

inline int digit(const string& A, int B) { return A[B]; }

int NULLdigit = 0;

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

    void searchR(link h, string str, const Key& v, int d) {
        int i = digit(v, d);
        if (h == 0) return;
        if (i == NULLdigit && h->d == NULLdigit) {
            cout << str << ' ';
            return;
        }
        if (i == h->d) {
            searchR(h->m, str + char(h->d), v, d + 1);
            return;
        }
        if (i == '*') {
            searchR(h->m, str + char(h->d), v, d + 1);
        }
        searchR(h->l, str, v, d);
        searchR(h->r, str, v, d);
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
    void search(const Key& v) { searchR(head, "", v, 0); }
    void insert(Item x) { insertR(head, x, 0); }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    TST<Item, Key> st;

    vector<string> svec = {"NOW", "IS", "THE", "FOR", "TIME", "THEORY", "IO"};

    for (size_t i = 0; i < svec.size(); ++i) {
        std::cout << std::setw(6) << svec[i] << ": ";
        for (size_t j = 0; j <= svec[i].size(); ++j) {
            std::cout << std::setw(3) << digit(svec[i], j) << ' ';
        }
        std::cout << endl;
        st.insert(svec[i]);
    }

    cout << "I*: ";
    st.search("I*");
    cout << endl;
    
    cout << "*O*: ";
    st.search("*O*");
    cout << endl;

    cout << "TH*: ";
    st.search("TH*");
    cout << endl;

    cout << "TIME: ";
    st.search("TIME");
    cout << endl;

    cout << "****: ";
    st.search("****");
    cout << endl;

    cout << "***: ";
    st.search("***");
    cout << endl;

    cout << "ok\n";
}
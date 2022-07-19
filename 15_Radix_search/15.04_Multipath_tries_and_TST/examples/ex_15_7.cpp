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
class DST {
   private:
    struct node {
        node **next;
        node() {
            next = new node *[Num];
            for (size_t i = 0; i < Num; i++) next[i] = 0;
        }
    };
    typedef node *link;
    link head;
    Item nullItem;

    Item searchR(link h, Key v, int d) {
        int i = digit(v, d);
        if (h == 0) return nullItem;
        if (i == NULLdigit) {
            Item dummy(v);
            return dummy;
        }
        return searchR(h->next[i], v, d + 1);
    }
    void insertR(link& h, Item x, int d) {
        int i = digit(x.key(), d);
        if (h == 0) h = new node;
        if (i == NULLdigit) return;
        insertR(h->next[i], x, d + 1);
    }

   public:
    DST() { head = 0; }
    Item search(Key v) { return searchR(head, v, 0); }
    void insert(Item x) { insertR(head, x, 0); }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    DST<Item, Key, 'Z' - 'A'> st;

    vector<string> svec = {"NOW", "IS", "THE", "FOR", "TIME"};

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
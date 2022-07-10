#include <cassert>
#include <iostream>

using namespace std;

static int maxKey = 1000;
typedef int Key;

class Item {
   private:
    Key keyval;
    float info;

   public:
    Item() { keyval = maxKey; }
    Item(Key key) { keyval = key; }
    Key key() { return keyval; }
    int null() { return keyval = maxKey; }
    void rand() {
        keyval = 1000 * ::rand() / RAND_MAX;
        info = 1.0 * ::rand() / RAND_MAX;
    }
    int scan(istream& is = cin) { return !!(is >> keyval >> info); }
    void show(ostream& os = cout) { os << keyval /*<< " " << info*/ << endl; }
};

ostream& operator<<(ostream& os, Item& x) {
    x.show(os);
    return os;
}

template <class Item, class Key>
class ST {
   private:
    struct node {
        Item item;
        node *l, *r;
        node(Item x) {
            item = x;
            l = 0;
            r = 0;
        }
    };

    typedef node* link;

    link head;
    Item nullItem;

    Item searchR(link h, Key v) {
        if (h == 0) return nullItem;
        Key t = h->item.key();
        if (v == t) return h->item;
        if (v < t)
            return searchR(h->l, v);
        else
            return searchR(h->r, v);
    }

    void insertR(link& h, Item x) {
        if (h == 0) {
            h = new node(x);
            return;
        }
        if (x.key() < h->item.key())
            insertR(h->l, x);
        else
            insertR(h->r, x);
    }

    void showR(link h, ostream& os) {
        if (h == 0) return;
        showR(h->l, os);
        h->item.show(os);
        showR(h->r, os);
    }

   public:
    ST([[maybe_unused]] int maxN) { head = 0; }
    Item search(Key v) { return searchR(head, v); }
    void insert(Item x) { insertR(head, x); }

    void show(ostream& os) { showR(head, os); }

    template <typename T>
    void print_node(T item, size_t offset) {
        for (size_t i = 0; i != offset; ++i) cout << ' ';
        cout << item;
    }

    void print(size_t offset = 2, size_t start_offset = 0) { print(head, offset, start_offset); }

    void print(link curr_node, size_t offset = 2, size_t start_offset = 0) {
        if (!curr_node) {
            print_node('*', start_offset);
            cout << endl;
            return;
        }

        if (!curr_node->l && !curr_node->r) {
            print_node(curr_node->item.key(), start_offset);
            print_node('-', 0);
            cout << endl;
        } else {
            print(curr_node->r, offset, start_offset + offset);

            print_node(curr_node->item.key(), start_offset);
            cout << endl;

            print(curr_node->l, offset, start_offset + offset);
        }
    }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    ST<Item, Key> st(10);
    st.insert({2});
    st.insert({3});
    st.insert({1});
    st.insert({1});
    st.insert({4});

    st.show(cout);

    cout << "ok\n";
}
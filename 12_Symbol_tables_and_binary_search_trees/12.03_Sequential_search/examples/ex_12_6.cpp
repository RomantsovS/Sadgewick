#include <iostream>
#include <vector>

using namespace std;

static const int maxKey = 10;
typedef int Key;

class Item {
   private:
    Key keyval;
    float info;

   public:
    Item() { keyval = maxKey; }
    Key key() const { return keyval; }
    int null() const { return keyval == maxKey; }
    void rand() {
        keyval = ::rand() % maxKey;
        info = 1.0 * ::rand() / RAND_MAX;
    }
    int scan(istream& is = cin) { return !!(is >> keyval >> info); }
    void show(ostream& os = cout) const { os << keyval << " " << info << endl; }
};

ostream& operator<<(ostream& os, Item& x) {
    x.show(os);
    return os;
}

template <class Item, class Key>
class ST {
   private:
    Item nullItem;
    struct node {
        Item item;
        node* next;
        node(Item x, node* t) {
            item = x;
            next = t;
        }
    };
    typedef node* link;
    int N;
    link head;
    Item searchR(link t, Key v) {
        if (t == 0) return nullItem;
        if (t->item.key() == v) return t->item;
        return searchR(t->next, v);
    }

   public:
    ST(int maxN) {
        head = 0;
        N = 0;
    }
    int count() { return N; }
    Item search(Key v) { return searchR(head, v); }
    void insert(Item x) {
        head = new node(x, head);
        N++;
    }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    int N, maxN = maxKey, sw = 1;
    ST<Item, Key> st(maxN);
    for (N = 0; N < 5; N++) {
        Item v;
        if (sw)
            v.rand();
        else if (!v.scan())
            break;
        cout << "insert: " << v.key() << endl;
        if (!(st.search(v.key())).null()) continue;
        st.insert(v);
    }

    for (size_t i = 0; i < 10; ++i) {
        Item v;
        v.rand();
        cout << "search: " << v.key() << ' ' << !st.search(v.key()).null() << endl;
    }
}
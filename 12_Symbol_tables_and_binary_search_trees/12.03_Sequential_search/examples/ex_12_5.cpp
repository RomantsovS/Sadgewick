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
    vector<Item> st;
    int N;

   public:
    ST(int maxN) {
        st.resize(maxN);
        N = 0;
    }
    int count() { return N; }
    void insert(Item x) {
        int i = N++;
        Key v = x.key();
        while (i > 0 && v < st[i - 1].key()) {
            st[i] = st[i - 1];
            i--;
        }
        st[i] = x;
    }
    Item search(Key v) const {
        int i = 0;
        for (; i < N; i++)
            if (!(st[i].key() < v)) break;
        if (v == st[i].key()) return st[i];
        return nullItem;
    }
    Item select(int k) { return st[k]; }
    void show(ostream& os) {
        int i = 0;
        while (i < N) st[i++].show(os);
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

    for(size_t i = 0; i < 10; ++i) {
        Item v;
        v.rand();
        cout << "search: " << v.key() << ' ' << !st.search(v.key()).null() << endl;
    }
}
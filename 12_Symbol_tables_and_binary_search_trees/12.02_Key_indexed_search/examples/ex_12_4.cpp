#include <iostream>
#include <vector>

using namespace std;

static int maxKey = 10;
typedef int Key;

class Item {
   private:
    Key keyval;
    float info;

   public:
    Item() { keyval = maxKey; }
    Key key() { return keyval; }
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
    int M;

   public:
    ST([[maybe_unused]] int maxN) {
        M = nullItem.key();
        st.resize(M, nullItem);
    }
    int count() {
        int N = 0;
        for (int i = 0; i < M; i++)
            if (!st[i].null()) N++;
        return N;
    }
    void insert(Item x) { st[x.key()] = x;
    }
    Item search(Key v) { return st[v]; }
    void remove(Item x) { st[x.key()] = nullItem;
    }
    Item select(int k) {
        for (int i = 0; i < M; i++)
            if (!st[i].null())
                if (k-- = 0) return st[i];
        return nullItem;
    }
    void show(ostream& os) {
        for (int i = 0; i < M; i++)
            if (!st[i].null()) st[i].show(os);
    }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    int N, maxN = maxKey, sw = 1;
    ST<Item, Key> st(maxN);
    for (N = 0; N < maxN; N++) {
        Item v;
        if (sw)
            v.rand();
        else if (!v.scan())
            break;
        if (!(st.search(v.key())).null()) continue;
        st.insert(v);
        cout << endl;
        cout << N << " keys" << endl;
        cout << st.count() << " distinct keys" << endl;
    }
}
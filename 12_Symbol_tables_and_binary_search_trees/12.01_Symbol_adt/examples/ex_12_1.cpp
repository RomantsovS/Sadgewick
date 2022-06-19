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
    Key key() { return keyval; }
    int null() { return keyval = maxKey; }
    void rand() {
        keyval = 1000 * ::rand() / RAND_MAX;
        info = 1.0 * ::rand() / RAND_MAX;
    }
    int scan(istream& is = cin) { return !!(is >> keyval >> info); }
    void show(ostream& os = cout) { os << keyval << " " << info << endl; }
};

ostream& operator<<(ostream& os, Item& x) {
    x.show(os);
    return os;
}

template <class Item, class Key>
class ST {
   private:
    // Код, зависящий от реализации
   public:
    ST(int);
    int count();
    Item search(Key);
    void insert(Item);
    void remove(Item);
    Item select(int);
    void show(ostream&);
};

int main([[maybe_unused]] int argc, char* argv[]) {
    int N, maxN = atoi(argv[1]), sw = atoi (argv[2]);
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
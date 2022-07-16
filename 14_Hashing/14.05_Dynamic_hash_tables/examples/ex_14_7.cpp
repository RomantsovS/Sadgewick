#include <cassert>
#include <cmath>
#include <iostream>

using Key = int;

#include <Hash.h>
#include <Item.h>

template <typename Item, typename Key>
class HashTable {
   private:
    struct node {
        Item item;
        node* next;
        node(Item x, node* t) {
            item = x;
            next = t;
        }
    };

    using link = node*;

    Item* st;
    int N, M;
    Item nullItem;

    void expand() {
        Item* t = st;
        init(M + M);
        for (int i = 0; i < M / 2; i++)
            if (!t[i].null()) insert(t[i]);
        delete t;
    }

   public:
    HashTable(int maxN) { init(maxN); }
    void init(int maxN) {
        N = 0;
        M = maxN;
        st = new Item[M];
        for (int i = 0; i < M; ++i) st[i] = nullItem;
    }
    int count() const { return N; }
    int size() const { return M; }
    void insert(Item item) {
        int i = hash(item.key(), M);
        while (!st[i].null()) i = (i + 1) % M;
        st[i] = item;
        if (N++ >= M / 2) expand();
    }
    Item search(Key v) {
        int i = hash(v, M), k = hashtwo(v);
        while (!st[i].null())
            if (v == st[i].key())
                return st[i];
            else
                i = (i + k) % M;
        return nullItem;
    }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    HashTable<Item, Key> ht(1);
    ht.insert(1);
    std::cout << "count: " << ht.count() << ", size: " << ht.size() << std::endl;
    ht.insert(2);
    std::cout << "count: " << ht.count() << ", size: " << ht.size() << std::endl;
    ht.insert(11);
    std::cout << "count: " << ht.count() << ", size: " << ht.size() << std::endl;
    ht.insert(5);
    std::cout << "count: " << ht.count() << ", size: " << ht.size() << std::endl;
    ht.insert(6);
    std::cout << "count: " << ht.count() << ", size: " << ht.size() << std::endl;

    std::cout << ht.search(1).key() << std::endl;
    std::cout << ht.search(2).key() << std::endl;
    std::cout << ht.search(11).key() << std::endl;
    std::cout << ht.search(4).key() << std::endl;

    std::cout << "ok\n";
}
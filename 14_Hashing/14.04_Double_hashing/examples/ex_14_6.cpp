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

   public:
    HashTable(int maxN) {
        N = 0;
        M = 2 * maxN;
        st = new Item[M];
        for (int i = 0; i < M; ++i) st[i] = nullItem;
    }
    int count() const { return N; }
    void insert(Item item) {
        Key v = item.key();
        int i = hash(v, M), k = hashtwo(v);
        while (!st[i].null()) i = (i + k) % M;
        st[i] = item;
        N++;
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
    HashTable<Item, Key> ht(10);
    ht.insert(1);
    ht.insert(2);
    ht.insert(11);

    std::cout << ht.search(1).key() << std::endl;
    std::cout << ht.search(2).key() << std::endl;
    std::cout << ht.search(11).key() << std::endl;
    std::cout << ht.search(4).key() << std::endl;

    std::cout << "ok\n";
}
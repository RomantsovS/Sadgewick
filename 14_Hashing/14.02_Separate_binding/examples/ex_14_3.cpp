#include <cassert>
#include <cmath>
#include <iostream>

using Key = int;

#include <Hash.h>
#include <Item.h>

template <typename Item, typename Key>
class HashTable {
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

    using link = node*;

    link* heads;
    int N, M;

    Item searchR(link t, Key v) {
        if (t == 0) return nullItem;
        if (t->item.key() == v) return t->item;
        return searchR(t->next, v);
    }

   public:
    HashTable(int maxN) {
        N = 0;
        M = maxN / 5;
        heads = new link[M];
        for (int i = 0; i < M; i++) heads[i] = 0;
    }
    Item search(Key v) { return searchR(heads[hash(v, M)], v); }
    void insert(Item item) {
        int i = hash(item.key(), M);
        heads[i] = new node(item, heads[i]);
        N++;
    };
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    HashTable<Item, Key> ht(10);
    ht.insert(1);
    ht.insert(2);
    ht.insert(3);

    std::cout << ht.search(1).key() << std::endl;
    std::cout << ht.search(2).key() << std::endl;
    std::cout << ht.search(3).key() << std::endl;
    std::cout << ht.search(4).key() << std::endl;

    std::cout << "ok\n";
}
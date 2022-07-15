#pragma once

int hash(char* v, int M) {
    int h = 0, a = 127;
    for (; *v != 0; v++) {
        h = (a * h + *v) % M;
    }
    return h;
}

inline int hash(Key v, int M) { return v & (M - 1); }

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
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
        int i = hash(item.key(), M);
        while (!st[i].null()) i = (i + 1) % M;
        st[i] = item;
        N++;
    }
    Item search(Key v) {
        int i = hash(v, M);
        while (!st[i].null()) {
            if (v == st[i].key())
                return st[i];
            else
                i = (i + 1) % M;
        }
        return nullItem;
    }
    void remove(Item x) {
        int i = hash(x.key(), M), j;
        while (!st[i].null())
            if (x.key() == st[i].key())
                break;
            else
                i = (i + 1) % M;
        if (st[i].null()) return;
        st[i] = nullItem;
        N--;
        for (j = i + 1; !st[j].null(); j = (j + 1) % M, N--) {
            Item v = st[j];
            st[j] = nullItem;
            insert(v);
        }
    }
};
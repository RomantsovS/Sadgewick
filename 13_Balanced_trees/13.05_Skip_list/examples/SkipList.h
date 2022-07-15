#pragma once

const int lgNmax = 5;

template <typename Item, typename Key>
class SkipList {
   public:
    SkipList() {
        head = new node(nullItem, lgNmax);
        lgN = 0;
    }

    Item search(Key v) { return searchR(head, v, lgN); }

    void insert(Item v) { insertR(head, new node(v, randX()), lgN); }

    void remove(Item x) { removeR(head, x.key(), lgN); }

   private:
    struct node {
        Item item;
        node** next;
        int sz;
        node(Item x, int k) {
            item = x;
            sz = k;
            next = new node*[k];
            for (int i = 0; i < k; i++) next[i] = 0;
        }
    };
    using link = node*;
    link head;
    Item nullItem;
    int lgN;

    Item searchR(link t, Key v, int k) {
        if (t == 0) return nullItem;
        if (v == t->item.key()) return t->item;
        link x = t->next[k];
        if ((x == 0) || (v < x->item.key())) {
            if (k == 0) return nullItem;
            return searchR(t, v, k - 1);
        }
        return searchR(x, v, k);
    }

    int randX() {
        int i, j, t = rand();
        for (i = 1, j = 2; i < lgNmax; i++, j += j)
            if (t > RAND_MAX / j) break;
        if (i > lgN) lgN = i;
        return i;
    }
    void insertR(link t, link x, int k) {
        Key v = x->item.key();
        link tk = t->next[k];
        if ((tk == 0) || (v < tk->item.key())) {
            if (k < x->sz) {
                x->next[k] = tk;
                t->next[k] = x;
            }
            if (k == 0) return;
            insertR(t, x, k - 1);
            return;
        }
        insertR(tk, x, k);
    }

    void removeR(link t, Key v, int k) {
        link x = t->next[k];
        if (x == 0 || !(x->item.key() < v)) {
            if (x && v == x->item.key()) {
                t->next[k] = x->next[k];
            }
            if (k == 0) {
                delete x;
                return;
            }
            removeR(t, v, k - 1);
            return;
        }
        removeR(t->next[k], v, k);
    }
};
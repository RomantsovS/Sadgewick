#include <cassert>
#include <iostream>
#include <stack>

const int bitsword = 5;
const int bitsbyte = 1;
const int bytesword = bitsword / bitsbyte;
const int R = 1 << bitsbyte;

inline int digit(long A, int B) {
    return ((A - 'A' + 1) >> bitsbyte * (bytesword - B - 1)) & (R - 1);
}

template <class Item, class Key>
class DST {
   private:
    struct node {
        Item item;
        node *l, *r;
        node(Item x) {
            item = x;
            l = 0;
            r = 0;
        }
        size_t N = 1;
        int bit = -1;
    };

    typedef node* link;

    link head;
    Item nullItem;

    Item searchR(link h, Key v, int d) {
        if (h->bit <= d) return h->item;
        if (digit(v, h->bit) == 0)
            return searchR(h->l, v, h->bit);
        else
            return searchR(h->r, v, h->bit);
    }

    link insertR(link h, Item x, int d, link p) {
        Key v = x.key();
        if ((h->bit >= d) || (h->bit <= p->bit)) {
            link t = new node(x);
            t->bit = d;
            t->l = (digit(v, t->bit) ? h : t);
            t->r = (digit(v, t->bit) ? t : h);
            return t;
        }
        if (digit(v, h->bit) == 0)
            h->l = insertR(h->l, x, d, h);
        else
            h->r = insertR(h->r, x, d, h);
        return h;
    }

    void showR(link h, std::ostream& os, int d) {
        if (h->bit <= d) {
            h->item.show(os);
            return;
        }
        showR(h->l, os, h->bit);
        showR(h->r, os, h->bit);
    }

   public:
    DST() {
        head = new node(nullItem);
        head->l = head->r = head;
    }

    Item search(Key v) {
        Item t = searchR(head->l, v, -1);
        return (v == t.key()) ? t : nullItem;
    }
    void insert(Item x) {
        Key v = x.key();
        int i;
        Key w = searchR(head->l, v, -1).key();
        if (v == w) return;
        for (i = 0; digit(v, i) == digit(w, i); ++i)
            ;
        head->l = insertR(head->l, x, i, head);
    }
    void show(std::ostream& os) { showR(head->l, os, -1); }
};
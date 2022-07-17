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
    };

    typedef node* link;

    link head;
    Item nullItem;

    Item searchR(link h, Key v, int d) {
        if (h == 0) return nullItem;
        if (v == h->item.key()) return h->item;
        if (digit(v, d) == 0)
            return searchR(h->l, v, d + 1);
        else
            return searchR(h->r, v, d + 1);
    }

    void insertR(link& h, Item x, int d) {
        if (h == 0) {
            h = new node(x);
            return;
        }
        if (digit(x.key(), d) == 0)
            insertR(h->l, x, d + 1);
        else
            insertR(h->r, x, d + 1);
    }

   public:
    DST() { head = 0; }

    Item search(Key v) { return searchR(head, v, 0); }
    void insert(Item x) { insertR(head, x, 0); }

    template <typename T>
    void print_node(T item, size_t offset) {
        for (size_t i = 0; i != offset; ++i) cout << ' ';
        cout << item;
    }

    void print(size_t offset = 2, size_t start_offset = 0) { print(head, offset, start_offset); }

    void print(link curr_node, size_t offset = 2, size_t start_offset = 0) {
        if (!curr_node) {
            print_node('*', start_offset);
            cout << endl;
            return;
        }

        if (!curr_node->l && !curr_node->r) {
            print_node(curr_node->item.key(), start_offset);
            print_node('-', 0);
            cout << endl;
        } else {
            print(curr_node->r, offset, start_offset + offset);

            print_node(curr_node->item.key(), start_offset);
            cout << endl;

            print(curr_node->l, offset, start_offset + offset);
        }
    }
};
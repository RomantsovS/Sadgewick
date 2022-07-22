#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const std::string red_str("\033[0;31m");
std::string reset_str("\033[0m");

using Key = int;
Key maxKey = 1000;

#include <Item.h>

const size_t M = 6;

template <class Item, class Key>
struct entry {
    Key key;
    Item item;
    struct node *next;
};
struct node {
    size_t m;
    entry<Item, Key> b[M];
    node() { m = 0; }
};
using link = node *;

template <typename Item, typename Key>
class BTREE {
   private:
    Item nullItem;

    size_t N;
    size_t HT;
    link head;

    Item searchR(link h, Key v, int ht) {
        size_t j;
        if (ht == 0)
            for (j = 0; j < h->m; j++) {
                if (v == h->b[j].key) return h->b[j].item;
            }
        else
            for (j = 0; j < h->m; j++)
                if ((j + 1 == h->m) || (v < h->b[j + 1].key))
                    return searchR(h->b[j].next, v, ht - 1);
        return nullItem;
    }

    link split(link h) {
        link t = new node;
        for (size_t j = 0; j < M / 2; j++) t->b[j] = h->b[M / 2 + j];
        h->m = M / 2;
        t->m = M / 2;
        return t;
    }

    link insertR(link h, Item x, int ht) {
        size_t i, j;
        Key v = x.key();
        entry<Item, Key> t;
        t.key = v;
        t.item = x;
        if (ht == 0)
            for (j = 0; j < h->m; j++) {
                if (v < h->b[j].key) break;
            }
        else
            for (j = 0; j < h->m; j++)
                if ((j + 1 == h->m) || (v < h->b[j + 1].key)) {
                    link u;
                    u = insertR(h->b[j++].next, x, ht - 1);
                    if (u == 0) return 0;
                    t.key = u->b[0].key;
                    t.next = u;
                    break;
                }
        for (i = h->m; i > j; i--) h->b[i] = h->b[i - 1];
        h->b[j] = t;
        if (++h->m < M)
            return 0;
        else
            return split(h);
    }

    void printR(link h, int ht, Key key = maxKey) {
        if (ht == 0) {
            for (size_t j = 0; j < h->m; j++) {
                cout << string(5 * (HT - ht), ' ')
                     << (h->b[j].item.key() == key ? red_str : reset_str)
                     << to_string(h->b[j].item.key()) << reset_str << endl;
            }
            cout << string(5 * (HT - ht), ' ') << "_____\n";
        } else {
            for (size_t j = 0; j < h->m; j++) {
                printR(h->b[j].next, ht - 1, key);
                if (j == h->m / 2) {
                    for (size_t k = 0; k < h->m; k++) {
                        cout << string(5 * (HT - ht), ' ') << to_string(h->b[k].key) << endl;
                    }
                }
            }
        }
    }

   public:
    BTREE() {
        N = 0;
        HT = 0;
        head = new node;
    }

    Item search(Key v) { return searchR(head, v, HT); }

    void insert(Item item) {
        link u = insertR(head, item, HT);
        if (u == 0) return;
        link t = new node();
        t->m = 2;
        t->b[0].key = head->b[0].key;
        t->b[1].key = u->b[0].key;
        t->b[0].next = head;
        t->b[1].next = u;
        head = t;
        HT++;
    }

    std::size_t replace_all(std::string &inout, std::string_view what, std::string_view with) {
        std::size_t count{};
        for (std::string::size_type pos{};
             inout.npos != (pos = inout.find(what.data(), pos, what.length()));
             pos += with.length(), ++count) {
            inout.replace(pos, what.length(), with.data(), with.length());
        }
        return count;
    }

    void print(Key key = maxKey) { printR(head, HT, key); }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[]) {
    BTREE<Item, Key> btree;

    vector<int> svec = {706, 176, 601, 153, 513, 773, 742, 373, 527, 766, 275,
                        737, 574, 434, 641, 207, 111, 227, 61,  736, 526 , 562, 17, 107, 147};

    for (size_t i = 0; i < svec.size(); ++i) {
        btree.insert(svec[i]);

        for (size_t j = 0; j <= i; ++j) {
            assert(btree.search(svec[i]).key() == svec[i]);
        }

        btree.print(svec[i]);
        cout << "===============\n";
    }

    assert(btree.search(0).null());

    cout << "ok\n";
}
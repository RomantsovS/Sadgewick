#include <cassert>
#include <iostream>
#include <stack>

template <class Item, class Key>
class ST {
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

    Item searchR(link h, Key v) {
        if (h == 0) return nullItem;
        Key t = h->item.key();
        if (v == t) return h->item;
        if (v < t)
            return searchR(h->l, v);
        else
            return searchR(h->r, v);
    }

    void insertR(link& h, Item x) {
        if (h == 0) {
            h = new node(x);
            return;
        }
        if (static_cast<size_t>(rand()) < RAND_MAX / (h->N + 1)) {
            insertT(h, x);
            return;
        }
        if (x.key() < h->item.key())
            insertR(h->l, x);
        else
            insertR(h->r, x);
        fixN(h);
    }

    void fixN(link h) {
        if(!h)
            return;
        h->N = 1;
        if (h->l) h->N += h->l->N;
        if (h->r) h->N += h->r->N;
    }

    void showR(link h, std::ostream& os) {
        if (h == 0) return;
        showR(h->l, os);
        h->item.show(os);
        showR(h->r, os);
    }

    void rotR(link& h) {
        link x = h->l;
        h->l = x->r;
        x->r = h;
        fixN(h);
        h = x;
        fixN(h);
    }

    void rotL(link& h) {
        link x = h->r;
        h->r = x->l;
        x->l = h;
        fixN(h);
        h = x;
        fixN(h);
    }

    void insertT(link& h, Item x) {
        if (h == 0) {
            h = new node(x);
            return;
        }
        if (x.key() < h->item.key()) {
            insertT(h->l, x);
            rotR(h);
        } else {
            insertT(h->r, x);
            rotL(h);
        }
    }

    Item selectR(link h, int k) {
        if (h == 0) return nullItem;
        int t = (h->l == 0) ? 0 : h->l->N;
        if (t > k) return selectR(h->l, k);
        if (t < k) return selectR(h->r, k - t - 1);
        return h->item;
    }

    void partR(link& h, int k) {
        int t = (h->l == 0) ? 0 : h->l->N;

        if (t > k) {
            partR(h->l, k);
            rotR(h);
        }
        if (t < k) {
            partR(h->r, k - t - 1);
            rotL(h);
        }
    }

    link joinLR(link a, link b) {
        if (a == 0) return b;
        if (b == 0) return a;
        if (rand() / (RAND_MAX / (a->N + b->N) + 1) < a->N) {
            a->r = joinLR(a->r, b);
            return a;
        } else {
            b->l = joinLR(a, b->l);
            return b;
        }
    }

    void removeR(link& h, Key v) {
        if (h == 0) return;
        Key w = h->item.key();
        if (v < w) removeR(h->l, v);
        if (w < v) removeR(h->r, v);
        if (v == w) {
            link t = h;
            h = joinLR(h->l, h->r);
            delete t;
        }
        fixN(h);
    }

    link joinR(link a, link b) {
        if (b == 0) return a;
        if (a == 0) return b;
        insertR(b, a->item);
        b->l = joinR(a->l, b->l);
        b->r = joinR(a->r, b->r);
        delete a;
        fixN(b);
        return b;
    }

    void balanceR(link& h) {
        if (h == 0 || h->N == 1) return;
        partR(h, h->N / 2);
        balanceR(h->l);
        balanceR(h->r);
    }

   public:
    ST() { head = 0; }
    Item search(Key v) { return searchR(head, v); }
    void insert(Item x) { insertR(head, x); }

    void show(std::ostream& os) { showR(head, os); }

    template <typename T>
    void print_node(T item, size_t offset) {
        for (size_t i = 0; i != offset; ++i) std::cout << ' ';
        std::cout << item;
    }

    void rotHeadR() { rotR(head); }
    void rotHeadL() { rotL(head); }

    void insertWithRotation(Item item) { insertT(head, item); }
    void insertWithRotationUnrecursive(Item x) {
        Key v = x.key();
        if (head == 0) {
            head = new node(x);
            return;
        }

        std::stack<link> st;

        link p = head;
        for (link q = p; q != 0; p = q ? q : p) {
            st.push(p);
            q = (v < q->item.key()) ? q->l : q->r;
        }

        link cur;
        if (v < p->item.key()) {
            p->l = new node(x);
            cur = p->l;
        } else {
            p->r = new node(x);
            cur = p->r;
        }

        while (!st.empty()) {
            link pp = st.top();
            st.pop();
            if (cur->item.key() < pp->item.key()) {
                pp->l = cur;
                rotR(pp);
            } else {
                pp->r = cur;
                rotL(pp);
            }
        }
        head = cur;
    }

    Item select(int k) { return selectR(head, k); }

    void remove(Item x) { removeR(head, x.key()); }

    void join(ST<Item, Key>& b) { head = joinR(head, b.head); }

    Item selectUnrecursive(int k) {
        if (head == 0) return nullItem;
        link h = head;

        while (true) {
            int t = (h->l == 0) ? 0 : h->l->N;
            if (t > k)
                h = h->l;
            else if (t < k) {
                h = h->r;
                k = k - t - 1;
            } else
                return h->item;
        }
    }

    void balance() { balanceR(head); }

    void print(size_t offset = 2, size_t start_offset = 0) { print(head, offset, start_offset); }

    void print(link curr_node, size_t offset = 2, size_t start_offset = 0) {
        if (!curr_node) {
            print_node('*', start_offset);
            std::cout << std::endl;
            return;
        }

        if (!curr_node->l && !curr_node->r) {
            print_node(curr_node->item.key(), start_offset);
            std::cout << '(' << curr_node->N << ')';
            print_node('-', 0);
            std::cout << std::endl;
        } else {
            print(curr_node->r, offset, start_offset + offset);

            print_node(curr_node->item.key(), start_offset);
            std::cout << '(' << curr_node->N << ')';
            std::cout << std::endl;

            print(curr_node->l, offset, start_offset + offset);
        }
    }
};
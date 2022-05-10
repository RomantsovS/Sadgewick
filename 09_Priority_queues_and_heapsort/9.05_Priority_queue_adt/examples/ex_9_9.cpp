#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

template <class Item>
class PQ {
   private:
    struct node {
        Item item;
        node *prev = nullptr, *next = nullptr;
        node(Item v) { item = v; }
    };
    typedef node* link;
    link head, tail;

   public:
    using handle = node*;
    PQ(int = 0) {
        head = new node(0);
        tail = new node(0);
        head->prev = tail;
        head->next = tail;
        tail->prev = head;
        tail->next = head;
    }
    int empty() const { return head->next->next == head; }
    handle insert(Item v) {
        handle t = new node(v);
        t->next = head->next;
        t->next->prev = t;
        t->prev = head;
        head->next = t;
        return t;
    }
    Item getmax() {
        Item max;
        link x = head->next;
        for (link t = x; t->next != head; t = t->next)
            if (x->item < t->item) x = t;
        max = x->item;
        remove(x);
        return max;
    }
    void change(handle x, Item v) { x->key = v; }
    void remove(handle x) {
        x->next->prev = x->prev;
        x->prev->next = x->next;
        delete x;
    }
    void join(PQ<Item>& p) {
        tail->prev->next = p.head->next;
        p.head->next->prev = tail->prev;
        head->prev = p.tail;
        p.tail->next = head;
        delete tail;
        delete p.head;
        tail = p.tail;
    }
};

int main() {
    {
        PQ<int> pq;

        pq.insert(1);
        assert(!pq.empty());
        assert(pq.getmax() == 1);
        assert(pq.empty());
    }
    {
        PQ<int> pq;

        pq.insert(1);
        pq.insert(10);
        pq.insert(3);
        pq.insert(5);

        assert(pq.getmax() == 10);
        assert(pq.getmax() == 5);
        assert(pq.getmax() == 3);
        assert(pq.getmax() == 1);
        assert(pq.empty());
    }
    {
        PQ<int> pq;

        pq.insert(1);
        pq.insert(10);
        pq.insert(3);
        pq.insert(5);

        assert(pq.getmax() == 10);
        assert(pq.getmax() == 5);
        assert(pq.getmax() == 3);
        pq.insert(10);
        assert(pq.getmax() == 10);
        assert(pq.getmax() == 1);
        assert(pq.empty());
    }

    cout << "ok\n";

    return 0;
}
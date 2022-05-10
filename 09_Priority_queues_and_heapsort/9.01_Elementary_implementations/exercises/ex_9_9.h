#include <List.h>

template <class Item>
class PQOrderedList {
   private:
    link<Item> head = nullptr, tail = nullptr;

   public:
    int empty() const { return head == nullptr; }
    void insert(Item item) {
        if (empty()) {
            tail = head = new node<Item>(item);
        } else {
            auto iter = head;
            while (iter && iter->item <= item) {
                iter = iter->next;
            }
            auto n = new node<Item>(item);
            if (!iter) {
                tail->next = n;
                n->prev = tail;
                tail = tail->next;
            } else {
                if (iter->prev)
                    iter->prev->next = n;
                else
                    head = n;
                n->next = iter;
                n->prev = iter->prev;
                iter->prev = n;
            }
        }
    }
    Item getmax() {
        auto res = tail->item;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;
        return res;
    }
};
#pragma once

#include <List.h>

#include <algorithm>

template <class Item>
class PQUnorderedList {
   private:
    link<Item> head = nullptr, tail = nullptr;

   public:
    int empty() const { return head == nullptr || head->next == nullptr; }
    void insert(Item item) {
        if (empty()) {
            head = new node<Item>();
            tail = head->next = new node<Item>(item);
        } else {
            tail->next = new node<Item>(item);
            tail = tail->next;
        }
    }
    Item getmax() {
        link<Item> max = head;
        for (auto iter = head; iter->next; iter = iter->next) {
            if (max->next->item < iter->next->item) max = iter;
        }
        if (max == head) {
            if (tail == head->next) tail = tail->next;
            max = max->next;
            head->next = head->next->next;
            return max->item;
        }
        link<Item> res = max->next;
        if (tail == max->next) tail = max;
        max->next = max->next->next;
        return res->item;
    }
};
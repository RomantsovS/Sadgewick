#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <memory>
#include <stack>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
struct node {
    node() : next(nullptr) {}
    node(T x, node<T> *t = nullptr, node<T> *p = nullptr) : item(x), next(t), prev(p) {}

    T item;
    node<T> *next;
    node<T> *prev;
};

template <typename T>
using link = node<T> *;

template <typename T>
link<T> freelist = nullptr;

template <typename T>
void construct(int N) {
    freelist<T> = new node<T>[N + 1];

    for (size_t i = 0; i != N; ++i) {
        freelist<T>[i].next = &freelist<T>[i + 1];
    }
}

template <typename T>
void destruct() {
    delete[] freelist<T>;
}

template <typename T>
void insert(link<T> x, link<T> t) {
    t->next = x->next;
    x->next = t;
}

template <typename T>
link<T> remove(link<T> x) {
    link<T> t = x->next;
    x->next = t->next;
    return t;
}

template <typename T>
link<T> newNode(int i) {
    link<T> x = remove(freelist<T>);
    x->item = i;
    x->next = x;

    return x;
}

template <typename T>
void deleteNode(link<T> x) {
    insert(freelist<T>, x);
}

template <typename T>
link<T> newNodeN(T i) {
    auto t = new node<T>(i);

    // cout << "new " << t << endl;

    return t;
}

template <typename T>
void deleteNodeN(link<T> x) {
    // cout << "del " << x << endl;
    delete x;
}

template <typename T>
link<T> next(link<T> x) {
    return x->next;
}

template <typename T>
int item(link<T> x) {
    return x->item;
}

template <typename T>
void printList(link<T> t) {
    if (!t) {
        cout << "Empty link\n";
        return;
    }

    auto x = t;

    do {
        cout << x->item << " ";

        x = x->next;
    } while (x != t && x);

    cout << endl;
}

template <typename T>
link<T> generateList(size_t len, T start) {
    auto t = newNodeN<T>(start);

    auto x = t;

    for (size_t i = 1; i < len; ++i) {
        x = (x->next = newNodeN<T>(start + i));
    }

    return t;
}

template <typename T>
link<T> generateRandList(size_t len, T min_val, T max_val) {
    auto t = new node<T>(min_val + rand() % (max_val - min_val), 0);

    auto x = t;

    for (size_t i = 1; i < len; ++i) {
        x = (x->next = new node<T>(min_val + rand() % (max_val - min_val), 0));
    }

    return t;
}

template <typename T>
link<T> generateCircularList(size_t len, int start) {
    auto t = new node<T>(start, 0);

    auto x = t;

    for (size_t i = 1; i < len; ++i) {
        x = (x->next = new node<T>(start + i));
    }

    x->next = t;

    return t;
}

template <typename T>
void delete_list(link<T> &a) {
    if (!a) return;

    std::stack<link<T>> st;

    while (a) {
        st.push(a);
        a = a->next;
    }

    while (!st.empty()) {
        auto t = st.top();
        delete t;
        st.pop();
    }
}

template <typename T>
void inverse_list(link<T> &x) {
    link<T> r = 0, y = x, t;

    while (y) {
        t = y->next;

        y->next = r;

        r = y;

        y = t;
    }

    x = r;
}

template <typename T>
void sort_list(link<T> &a) {
    // link<T> b = new node<T>(), x, u, t;
    auto b = std::make_shared<node<T>>();
    link<T> x, u, t;

    for (t = a; t != 0; t = u) {
        u = t->next;

        for (x = b.get(); x->next != 0; x = x->next) {
            if (x->next->item > t->item) break;
        }

        t->next = x->next;
        x->next = t;
    }

    a = b->next;
}

template <typename T>
class CList;

template <typename T>
class CList {
   public:
    struct node {
        node() : next(nullptr) {}
        node(T x, std::shared_ptr<node> t = nullptr) : item(x), next(t) {}

        T item;
        std::shared_ptr<node> next;
    };

    CList() : head(nullptr), curr(head) {}
    CList(size_t N, T max_val) {
        while (N-- > 0) {
            emplace(rand() % max_val);
        }
    }

    std::shared_ptr<node> &get_head() { return head; }

    void insert(std::shared_ptr<node> x, std::shared_ptr<node> t);
    void emplace(T val, std::shared_ptr<node> t = nullptr);

    void remove(std::shared_ptr<node> x);

    bool empty();
    std::shared_ptr<node> next(std::shared_ptr<node> t) { return t->next; }

    void print(std::shared_ptr<node> curr_ptr = nullptr);
    void sort();

   private:
    std::shared_ptr<node> findmax(std::shared_ptr<node>);

    std::shared_ptr<node> head;
    std::shared_ptr<node> curr;
};

template <typename T>
inline void CList<T>::insert(std::shared_ptr<node> dest, std::shared_ptr<node> ptr) {
    ptr->next = dest->next;
    dest->next = ptr;
}

template <typename T>
inline void CList<T>::emplace(T val, std::shared_ptr<node> t) {
    if (!t) t = curr;

    auto ptr = std::make_shared<node>(val);

    if (empty())
        curr = head = ptr;
    else {
        curr->next = ptr;
        curr = ptr;
    }
}

template <typename T>
inline void CList<T>::remove(std::shared_ptr<node> x) {
    auto t = x->next;

    if (x->next == head) head = t->next;

    x->next = t->next;
}

template <typename T>
inline bool CList<T>::empty() {
    return !head;
}

template <typename T>
void CList<T>::print(std::shared_ptr<node> curr_ptr) {
    if (empty()) cout << "list is empty\n";

    if (!curr_ptr) curr_ptr = head;

    auto start = curr_ptr;

    do {
        cout << curr_ptr->item << " ";
        curr_ptr = curr_ptr->next;
    } while (curr_ptr->next);

    cout << endl;
}

template <typename T>
void CList<T>::sort() {
    auto dummy = std::make_shared<node>();
    std::shared_ptr<node> start = dummy, out = nullptr;

    start->next = head;

    while (start->next) {
        auto max = findmax(start), t = max->next;

        max->next = t->next;
        t->next = out;
        out = t;
    }

    head = curr = out;
}

template <typename T>
std::shared_ptr<typename CList<T>::node> CList<T>::findmax(std::shared_ptr<node> h) {
    auto prev_max_node = h;
    T max = h->item;

    while (h->next) {
        if (h->next->item > max) {
            prev_max_node = h;
            max = h->next->item;
        }
        h = h->next;
    }

    return prev_max_node;
}

#endif
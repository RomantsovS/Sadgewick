#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
class CTree {
   public:
    struct node {
        node() : l(nullptr), r(nullptr) {}
        node(T x, node* _l = nullptr, node* _r = nullptr) : item(x), l(_l), r(_r) {}

        T item;
        node *l, *r;
    };

    CTree(node* _root = nullptr) : root(_root) {}
    CTree(const T first_val, const size_t size);

    node* get_root() { return root; }

    bool empty() const;

    node* l(node* t) { return t->l; }

    node* r(node* t) { return t->r; }

    node* add_val(const T val);
    node* add_val(const T val, node* dest, bool left);
    const node* find_node(const T val, const node* start_node = nullptr) const;

    node* get_rand_node();

    size_t num_nodes(node* cur_node) const;
    int height(node* cur_node) const;

    size_t num_leaves(node* cur_node) const;

    size_t internal_path_lenght(node* cur_node, size_t h) const;

   private:
    node* root;

    std::pair<size_t, node*> get_shortest_node(node* cur_node = nullptr);
};

template <typename T>
inline CTree<T>::CTree(const T first_val, const size_t size) {
    for (size_t i = 0; i != size; ++i) add_val(first_val + static_cast<T>(i));
}

template <typename T>
inline bool CTree<T>::empty() const {
    return !root;
}

template <typename T>
inline typename CTree<T>::node* CTree<T>::add_val(const T val) {
    if (!root) {
        root = new node(val);
        return root;
    }

    auto node = get_shortest_node(root);

    if (!node.second->l) {
        node.second->l = new CTree<T>::node(val);
        return node.second->l;
    }

    node.second->r = new CTree<T>::node(val);
    return node.second->r;
}

template <typename T>
inline typename CTree<T>::node* CTree<T>::add_val(const T val, node* dest, bool left) {
    if (!root) {
        root = new CTree<T>::node(val);
        return root;
    }

    if (left) {
        dest->l = new CTree<T>::node(val);
        return dest->l;
    }

    dest->r = new CTree<T>::node(val);
    return dest->r;
}

template <typename T>
inline const typename CTree<T>::node* CTree<T>::find_node(const T val, const node* start_node) const {
    if (!root) return nullptr;

    auto cur_node = start_node;

    if (!cur_node) cur_node = root;

    if (cur_node->item == val)
        return cur_node;
    else {
        if (cur_node->l) {
            auto node = find_node(val, cur_node->l);
            if (node) return node;
        }

        if (cur_node->r) {
            auto node = find_node(val, cur_node->r);
            if (node) return node;
        }
    }

    return nullptr;
}

template <typename T>
inline typename CTree<T>::node* CTree<T>::get_rand_node() {
    size_t h = rand() % num_nodes(root);
    size_t cur = 0;

    std::stack<decltype(root)> s;

    s.push(root);

    while (!s.empty()) {
        auto node = s.top();
        s.pop();

        if (cur != h)
            ++cur;
        else
            return node;

        if (node->r) s.push(node->r);
        if (node->l) s.push(node->l);
    }

    return nullptr;
}

template <typename T>
inline std::pair<size_t, typename CTree<T>::node*> CTree<T>::get_shortest_node(node* cur_node) {
    if (!cur_node) return std::make_pair(-1, nullptr);

    if (!cur_node->l || !cur_node->r) return std::make_pair(0, cur_node);

    auto p_l = get_shortest_node(cur_node->l);
    auto p_r = get_shortest_node(cur_node->r);

    if (p_l.first > p_r.first) return std::make_pair(p_r.first + 1, !p_r.second ? cur_node : p_r.second);
    return std::make_pair(p_l.first + 1, !p_l.second ? cur_node : p_l.second);
}

template <typename T>
void print_node(T item, size_t offset) {
    for (size_t i = 0; i != offset; ++i) cout << ' ';
    cout << item;
}

template <typename T>
void print(typename CTree<T>::node* curr_node, size_t offset = 2, size_t start_offset = 0) {
    if (!curr_node) {
        print_node('*', start_offset);
        cout << endl;
        return;
    }

    if (!curr_node->l && !curr_node->r) {
        print_node(curr_node->item, start_offset);
        print_node('-', 0);
        cout << endl;
    } else {
        // cout << endl;
        print<T>(curr_node->r, offset, start_offset + offset);

        print_node(curr_node->item, start_offset);
        cout << endl;

        print<T>(curr_node->l, offset, start_offset + offset);
    }
}

template <typename T>
size_t CTree<T>::num_nodes(node* cur_node) const {
    if (!cur_node) return 0;
    return num_nodes(cur_node->l) + num_nodes(cur_node->r) + 1;
}

template <typename T>
int CTree<T>::height(node* cur_node) const {
    if (!cur_node) return -1;

    int u = height(cur_node->l), v = height(cur_node->r);

    if (u > v)
        return u + 1;
    else
        return v + 1;
}

template <typename T>
size_t CTree<T>::num_leaves(node* cur_node) const {
    if (!cur_node)
        return 0;
    else if (!cur_node->l && !cur_node->r)
        return 1;

    return num_leaves(cur_node->l) + num_leaves(cur_node->r);
}

template <typename T>
size_t CTree<T>::internal_path_lenght(node* cur_node, size_t h) const {
    if (!cur_node) return 0;
    if (cur_node->l || cur_node->r)
        return h + internal_path_lenght(cur_node->l, h + 1) + internal_path_lenght(cur_node->r, h + 1);
    return 0;
}

template <typename T>
typename CTree<T>::node* max(const std::vector<T>& mas, size_t l, size_t r) {
    if (r < l) return nullptr;

    size_t m = (l + r) / 2;

    auto x = new typename CTree<T>::node(mas[m]);

    if (l == r) return x;

    x->l = max(mas, l, m);
    x->r = max(mas, m + 1, r);

    T u = x->l->item, v = x->r->item;

    if (u > v)
        x->item = u;
    else
        x->item = v;

    return x;
}

template <typename T>
CTree<T> generate_tree_max(const std::vector<T>& mas) {
    auto node = max<T>(mas, 0, mas.size() - 1);

    return CTree<T>(node);
}

template <typename T>
CTree<T> generate_tree_random(const size_t size, const T first_val, const T rand_max) {
    auto tree = CTree<T>(first_val + rand() % rand_max, 1);

    for (size_t i = 0; i < size - 1; ++i) {
        auto node = tree.get_rand_node();

        if (!node || node->l && node->r)
            tree.add_val(first_val + rand() % rand_max);
        else {
            if (!node->l && !node->r)
                tree.add_val(first_val + rand() % rand_max, node, rand() % 2);
            else if (node->l)
                tree.add_val(first_val + rand() % rand_max, node, false);
            else
                tree.add_val(first_val + rand() % rand_max, node, true);
        }
    }

    return tree;
}

#endif
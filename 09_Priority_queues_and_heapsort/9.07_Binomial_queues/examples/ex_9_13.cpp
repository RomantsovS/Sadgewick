#include <tree.h>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
using link = typename CTree<T>::node*;

template <typename T>
static link<T> pair_(link<T> p, link<T> q) {
    if (p->item < q->item) {
        p->r = q->l;
        q->l = p;
        return q;
    } else {
        q->r = p->l;
        p->l = q;
        return p;
    }
}

int main() {
    CTree<char> treeX('X', 1);
    auto nodeW = treeX.add_val('W', treeX.get_root(), true);
    auto nodeP = treeX.add_val('P', nodeW, true);
    auto nodeM = treeX.add_val('M', nodeW, false);
    print<char>(treeX.get_root());

    cout << "=================\n";

    CTree<char> treeT('T', 1);
    auto nodeS = treeT.add_val('S', treeT.get_root(), true);
    auto nodeR = treeT.add_val('R', nodeS, true);
    auto nodeN = treeT.add_val('N', nodeS, false);
    print<char>(treeT.get_root());

    cout << "=================\n";

    auto n = pair_<char>(treeX.get_root(), treeT.get_root());
    print<char>(n);

    return 0;
}
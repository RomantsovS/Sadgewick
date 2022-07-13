#include <cassert>
#include <iostream>

using Key = int;

#include "../../12.05_Binary_search_trees/examples/Key.h"
#include "../../12.05_Binary_search_trees/examples/ST.h"

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    ST<Item, Key> st;
    st.insert({1});
    st.insert({3});
    st.insert({5});
    st.insert({7});
    st.insert({9});

    st.print();

    for (size_t i = 0; i < 5; ++i) {
        cout << st.selectUnrecursive(i).key() << endl;
        cout << st.select(i).key() << endl;
    }

    cout << "ok\n";
}
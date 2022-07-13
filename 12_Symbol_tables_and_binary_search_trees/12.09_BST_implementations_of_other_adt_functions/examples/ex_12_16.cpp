#include <cassert>
#include <iostream>

using Key = int;

#include "../../12.05_Binary_search_trees/examples/Key.h"
#include "../../12.05_Binary_search_trees/examples/ST.h"

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    ST<Item, Key> st;
    st.insert({7});
    st.insert({1});
    st.insert({3});
    st.insert({9});
    st.insert({5});

    st.print();

    cout << "==============\n";

    st.remove(3);
    st.print();

    cout << "ok\n";
}
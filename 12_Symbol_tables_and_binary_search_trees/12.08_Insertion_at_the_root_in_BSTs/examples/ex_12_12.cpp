#include <cassert>
#include <iostream>

using Key = int;

#include "../../12.05_Binary_search_trees/examples/Key.h"
#include "../../12.05_Binary_search_trees/examples/ST.h"

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    ST<Item, Key> st;
    st.insert({2});
    st.insert({3});
    st.insert({1});
    st.insert({1});
    st.insert({4});

    st.print();

    st.rotHeadR();

    std::cout << "==========\n";

    st.print();

    st.rotHeadL();

    std::cout << "==========\n";

    st.print();

    cout << "ok\n";
}
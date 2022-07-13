#include <cassert>
#include <iostream>
#include <string>

using Key = char;

#include "../../12.05_Binary_search_trees/examples/Key.h"
#include "../../12.05_Binary_search_trees/examples/ST.h"

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    ST<Item, Key> st;
    string str = "GEMAIR";

    for(auto ch : str) {
        st.insert(ch);
    }

    st.print();

    cout << "==============\n";

    ST<Item, Key> st2;
    str = "NHXCSP";

    for(auto ch : str) {
        st2.insert(ch);
    }

    st2.print();

    cout << "==============\n";

    st.join(st2);
    st.print();

    cout << "ok\n";
}
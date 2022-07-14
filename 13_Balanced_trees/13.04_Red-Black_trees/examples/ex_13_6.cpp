#include <cassert>
#include <iostream>

using Key = char;

#include <Key.h>
#include "RBTree.h"

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    RBTree<Item, Key> st;
    string str = "ASERCHINGX";

    for(auto ch : str) {
        st.insert(ch);
        st.print();
        cout << endl;
    }

    cout << "ok\n";
}
#include <cassert>
#include <iostream>
#include <string>

using Key = char;

#include "../../12.05_Binary_search_trees/examples/Key.h"
#include "../../12.05_Binary_search_trees/examples/ST.h"

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    ST<Item, Key> st;
    
    string str = "EASYQUESTION";

    for(auto ch : str) {
        st.insertWithRotation(ch);
    }

    st.print();

    cout << "ok\n";
}
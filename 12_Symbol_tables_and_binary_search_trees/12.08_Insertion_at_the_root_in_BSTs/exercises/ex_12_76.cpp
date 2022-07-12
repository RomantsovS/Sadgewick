#include <cassert>
#include <iostream>
#include <string>
#include <sstream>

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
    cout << "===========\n";

    ST<Item, Key> st2;

    for(auto ch : str) {
        st2.insertWithRotationUnrecursive(ch);
    }

    st2.print();

    ostringstream oss1, oss2;
    st.show(oss1);
    st2.show(oss2);

    assert(oss1.str() == oss2.str());

    cout << "ok\n";
}
#include <cassert>
#include <iostream>

using Key = int;

#include <Key.h>
#include <ST.h>

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    ST<Item, Key> st;
    st.insertSplay({7});
    st.insertSplay({1});
    st.insertSplay({3});
    st.insertSplay({9});
    st.insertSplay({5});

    st.print();

    cout << "ok\n";
}
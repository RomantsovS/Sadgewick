#include <cassert>
#include <iostream>

using Key = int;

#include <Key.h>
#include <ST.h>

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    ST<Item, Key> st;
    st.insert({1});
    st.insert({3});
    st.insert({5});
    st.insert({7});
    st.insert({9});

    st.print();

    cout << "===========\n";
    st.balance();

    st.print();

    cout << "ok\n";
}
#include <cassert>
#include <iostream>

using Key = int;

#include <Key.h>
#include <ST.h>

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    srand(time(0));
    
    ST<Item, Key> st;
    st.insert({1});
    st.insert({3});
    st.insert({5});
    st.insert({7});
    st.insert({9});

    st.print();

    cout << "=========\n";

    ST<Item, Key> st2;
    st2.insert({0});
    st2.insert({2});
    st2.insert({4});
    st2.insert({6});
    st2.insert({8});

    st2.print();

    cout << "=========\n";
    st.join(st2);
    st.print();

    cout << "ok\n";
}
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

static char maxKey = 'z' + 1;
using Key = char;

#include <Item.h>
#include "DST.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    DST<Item, Key> st;

    std::string str = "ASERCHINGXMPL";

    for(auto ch : str) {
        std::cout << std::setw(4) << ch << ": ";
        for (size_t j = 0; j < bytesword; ++j) {
            std::cout << digit(ch, j);
        }
        std::cout << endl;
        st.insert(ch);
    }

    assert(st.search('A').key() == 'A');
    assert(st.search(0).null());

    st.print();

    cout << "ok\n";
}
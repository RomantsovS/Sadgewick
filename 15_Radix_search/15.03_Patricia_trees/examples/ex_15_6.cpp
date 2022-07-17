#include <cassert>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

static char maxKey = 0;
using Key = char;

#include <Item.h>

#include "DST.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    DST<Item, Key> st;

    std::string str = "ASERCH";

    std::cout << std::setw(4) << maxKey << ": ";
    for (size_t j = 0; j < bytesword; ++j) {
        std::cout << digit(maxKey, j);
    }
    std::cout << endl;

    for (auto ch : str) {
        std::cout << std::setw(4) << ch << ": ";
        for (size_t j = 0; j < bytesword; ++j) {
            std::cout << digit(ch, j);
        }
        std::cout << endl;
        st.insert(ch);
        
        st.show(cout);
        std::cout << "============\n";
    }


    cout << "ok\n";
}
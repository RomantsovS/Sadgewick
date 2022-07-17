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

    for (size_t i = 0; i < str.size(); ++i) {
        std::cout << std::setw(4) << str[i] << ": ";
        for (size_t j = 0; j < bytesword; ++j) {
            std::cout << digit(str[i], j);
        }
        std::cout << endl;
        st.insert(str[i]);

        for (size_t j = 0; j <= i; ++j) {
            assert(st.search(str[i]).key() == str[i]);
        }
    }

    cout << "ok\n";
}
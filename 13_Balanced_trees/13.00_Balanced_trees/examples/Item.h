#pragma once

#include <iostream>

class Item {
   private:
    Key keyval;
    float info;

   public:
    Item() { keyval = maxKey; }
    Item(Key key) { keyval = key; }
    Key key() { return keyval; }
    int null() { return keyval == maxKey; }
    void rand() {
        keyval = 1000 * ::rand() / RAND_MAX;
        info = 1.0 * ::rand() / RAND_MAX;
    }
    int scan(std::istream& is = std::cin) { return !!(is >> keyval >> info); }
    void show(std::ostream& os = std::cout) { os << keyval /*<< " " << info*/ << std::endl; }
};

std::ostream& operator<<(std::ostream& os, Item& x) {
    x.show(os);
    return os;
}
#include <cassert>
#include <cmath>
#include <iostream>

using Key = int;

#include <Item.h>
#include "HashTable.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    HashTable<Item, Key> ht(10);
    ht.insert(1);
    ht.insert(2);
    ht.insert(3);

    std::cout << ht.search(1).key() << std::endl;
    std::cout << ht.search(2).key() << std::endl;
    std::cout << ht.search(3).key() << std::endl;
    std::cout << ht.search(4).key() << std::endl;

    ht.remove(2);

    std::cout << ht.search(1).key() << std::endl;
    std::cout << ht.search(2).key() << std::endl;
    std::cout << ht.search(3).key() << std::endl;
    std::cout << ht.search(4).key() << std::endl;

    std::cout << "ok\n";
}
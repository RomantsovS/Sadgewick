#include <cassert>
#include <cmath>
#include <iostream>

#include "Hash.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    char ch[] = "test";
    std::cout << hash(ch, 127) << std::endl;

    std::cout << "ok\n";
}
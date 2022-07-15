#include <cassert>
#include <cmath>
#include <iostream>

int hash(char* v, int M) {
    int h = 0, a = 127;
    for (; *v != 0; v++) {
        h = (a * h + *v) % M;
    }
    return h;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    char ch[] = "test";
    std::cout << hash(ch, 127) << std::endl;

    std::cout << "ok\n";
}
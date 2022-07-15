#include <cassert>
#include <cmath>
#include <iostream>

int hashU(char* v, int M) {
    int h, a = 31415, b = 27183;
    for (h = 0; *v != 0; v++, a = a * b % (M - 1)) h = (a * h + *v) % M;
    return (h < 0) ? (h + M) : h;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    char ch[] = "test";
    std::cout << hashU(ch, 127) << std::endl;

    std::cout << "ok\n";
}
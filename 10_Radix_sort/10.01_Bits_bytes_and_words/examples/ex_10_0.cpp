#include <iostream>

using namespace std;

const int bitsword = 32;
const int bitsbyte = 8;
const int bytesword = bitsword / bitsbyte;
const int R = 1 << bitsbyte;

inline int digit(long A, int B) { return (A >> bitsbyte * (bytesword - B - 1)) & (R - 1); }

int main() {
    size_t n = 1025;

    for (size_t i = 0; i < 4; ++i) {
        cout << digit(n, i) << endl;
    }

    cout << "ok\n";

    return 0;
}
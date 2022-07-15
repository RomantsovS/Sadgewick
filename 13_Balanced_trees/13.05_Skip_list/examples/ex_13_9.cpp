#include <cassert>
#include <cmath>
#include <iostream>

using Key = char;

#include <Key.h>
#include "SkipList.h"

using namespace std;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    SkipList<Item, Key> sl;

    sl.insert('A');
    sl.insert('B');
    sl.insert('C');

    cout << sl.search('B').key() << endl;
    cout << sl.search('D').key() << endl;

    cout << "ok\n";
}
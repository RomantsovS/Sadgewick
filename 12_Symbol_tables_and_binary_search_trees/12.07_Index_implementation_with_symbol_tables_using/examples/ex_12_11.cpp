#include <fstream>
#include <iostream>
#include <cassert>
#include <sstream>
#include <string>

#include "../../12.05_Binary_search_trees/examples/ST.h"
#include "Item.h"

using namespace std;

const size_t maxN = 1000;

static char text[maxN];

int main() {
    size_t N = 0;
    char t;
    const size_t maxQ = 100;

    ifstream corpus;
    corpus.open("in.txt");
    while (N < maxN && corpus.get(t)) text[N++] = t;
    text[N] = 0;
    ST<Item, Key> st;
    for (size_t i = 0; i < N; i++) {
        st.insert(Key(&text[i]));
    }

    // st.print(1);
    // std::cout << "============\n";

    char query[maxQ];
    Item x, v(query);

    std::istringstream iss(R"(will
here
you
skills
according)");

    while (iss.getline(query, maxQ)) {
        if ((x = st.search(v.key())).null())
            cout << "not found: " << query << endl;
        else
            cout << x.key() - text << ": " << query << endl;
    }
}
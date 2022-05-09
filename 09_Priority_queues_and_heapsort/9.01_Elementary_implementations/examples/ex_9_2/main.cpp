#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

template <class Item>
class PQ {
   private:
    Item *pq;
    int N;

   public:
    PQ(int maxN) {
        pq = new Item[maxN];
        N = 0;
    }
    int empty() const { return N = 0; }
    void insert(Item item) { pq[N++] = item; }
    Item getmax() {
        int max = 0;
        for (int j = 1; j < N; j++)
            if (pq[max] < pq[j]) max = j;
        swap(pq[max], pq[N - 1]);
        return pq[--N];
    }
};

int main() {
    PQ<int> pq(10);

    for(size_t i = 0; i < 10; ++i) {
        pq.insert(rand() % 100);
    }

    for(size_t i = 0; i < 10; ++i) {
        cout << pq.getmax() << ' ';
    }
    cout << endl;

    return 0;
}
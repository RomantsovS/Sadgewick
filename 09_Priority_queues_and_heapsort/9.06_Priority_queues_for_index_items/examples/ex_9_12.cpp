#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Data {
    string name;
    int score;
};

const vector<Data> mas{{"Wilson", 63}, {"Johnson", 86}, {"Jones", 87}, {"Smith", 90}, {"Washington", 84}, {"Tompson", 65}};

struct Index {
    int item;
    explicit Index(int i = 0) { item = i; }
    operator int() const { return item; }
};

bool operator<(Index lhs, Index rhs) { return mas[lhs.item].score < mas[rhs.item].score; }

template <class Item>
class PQ {
   private:
    int N;
    vector<Index> pq;
    vector<int> qp;
    void exch(Index i, Index j) {
        int t;
        t = qp[i];
        qp[i] = qp[j];
        qp[j] = t;
        pq[qp[i]] = i;
        pq[qp[j]] = j;
    }

    void fixUp(Index a[], int k) {
        while (k > 1 && a[k / 2] < a[k]) {
            exch(a[k], a[k / 2]);
            k = k / 2;
        }
    }

    void fixDown(Index a[], int k, int n) {
        while (2 * k <= n) {
            int j = 2 * k;
            if (j < n && a[j] < a[j + 1]) j++;
            if (!(a[k] < a[j])) break;
            exch(a[k], a[j]);
            k = j;
        }
    }

   public:
    PQ(int maxN) {
        pq.resize(maxN + 1);
        qp.resize(maxN + 1);
        N = 0;
    }
    int empty() const { return N == 0; }
    void insert(Index v) {
        pq[++N] = v;
        qp[v] = N;
        fixUp(pq.data(), N);
    }
    Index getmax() {
        exch(pq[1], pq[N]);
        fixDown(pq.data(), 1, N - 1);
        return pq[N--];
    }
    void change(Index k) {
        fixUp(pq.data(), qp[k]);
        fixDown(pq.data(), qp[k], N);
    }
};

int main() {
    {
        PQ<int> pq(10);

        pq.insert(Index(0));
        assert(!pq.empty());
        auto index = pq.getmax();
        assert(index == 0);
        assert(mas[index].score == 63);
        assert(pq.empty());
    }

    {
        PQ<int> pq(10);

        pq.insert(Index(1));
        pq.insert(Index(2));
        pq.insert(Index(3));
        pq.insert(Index(4));
        pq.insert(Index(5));

        auto index = pq.getmax();
        assert(index == 3);
        assert(mas[index].score == 90);

        index = pq.getmax();
        assert(index == 2);
        assert(mas[index].score == 87);

        index = pq.getmax();
        assert(index == 1);
        assert(mas[index].score == 86);
    }

    cout << "ok\n";

    return 0;
}
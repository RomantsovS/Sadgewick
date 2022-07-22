#include <List.h>
#include <Queue.h>

#include <iostream>
#include <vector>

using namespace std;

const size_t V = 10;

void print(vector<link<int>>& adv, int i) {
    auto t = adv[i];

    while(t) {
        cout << t->item << "->";
        t = t->next;
    }

    cout << endl;
}

template <typename F>
void width_first_search(vector<link<int>>& adv, int k, vector<bool>& visited, F visit) {
    Queue<int> q(V * V);
    q.put(k);

    while(!q.empty()) {
        if(visited[k = q.get()] == 0) {
            visit(k);
            visited[k] = true;
            for(link<int> t = adv[k]; t; t = t->next) {
                if(visited[t->item == 0])
                    q.put(t->item);
            }
        }
    }
}

int main() {
    cout.setf(ios::unitbuf);
    
    int i, j;
    std::vector<int> ivec = {0, 7, 7, 1, 7, 2, 7, 4, 4, 6, 4, 5, 5, 3};

    vector<link<int>> adv(V);

    for (auto iter = ivec.cbegin(); iter != ivec.cend(); ++iter) {
        i = *iter;
        j = *(++iter);

        adv[j] = new node<int>(i, adv[i]);
        adv[i] = new node<int>(j, adv[i]);
    }

    for (i = 0; i != V; ++i) {
        print(adv, i);
    }

    cout << "=======\n";

    vector<bool> visited(V, false);

    width_first_search(adv, 0, visited, [](int k){
        cout << k;
        cout << endl;
    });

    return 0;
}
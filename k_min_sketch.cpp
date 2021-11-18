#include "bits/stdc++.h"

using namespace std;

void run();

signed main() { ios::sync_with_stdio(0); cin.tie(); cout << fixed << setprecision(13); run(); }

mt19937 rng(random_device{}());

uint32_t Hash(uint32_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = ((x >> 16) ^ x) * 0x45d9f3b;
    x = (x >> 16) ^ x;
    return x;
}

void run() {
    int n;
    cin >> n;
    set<int> a;

    uint32_t K = 50, L = UINT32_MAX;
    set<uint32_t> heap;
    for (int i = 0; i < n; ++i) {
        uint32_t d = rng() % 10000;
        a.insert(d);

        heap.insert(Hash(d));
        if (heap.size() > K)
            heap.erase(*heap.rbegin());
    }

    auto r = *heap.rbegin();
    cout << "Approximate: " << (uint64_t) K * L / r << endl;
    cout << "Actual: " << a.size() << endl;
}

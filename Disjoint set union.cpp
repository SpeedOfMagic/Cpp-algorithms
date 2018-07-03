
struct dsu {
    vector<int> repr;
    vector<int> siz;

    int fin(int a) {
        if (repr[a] == a)
            return a;
        else
            return repr[a] = fin(repr[a]);
    }

    void unite(int a, int b) {
        a = fin(a);
        b = fin(b);

        if (siz[a] > siz[b])
            swap(a, b);

        repr[a] = b;

        siz[b] += siz[a];
    }

    bool connected(int a, int b) {
        return fin(a) == fin(b);
    }

    dsu(int n) {
        for(int i = 0; i < n; i++) {
            repr.push_back(i);
            siz.push_back(1);
        }
    }
};

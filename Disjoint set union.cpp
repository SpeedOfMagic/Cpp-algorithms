struct dsu {
    vector<int> ancestor;
    vector<int> sizes;

    int find(int a) { return (ancestor[a] == a) ? a : ancestor[a] = find(ancestor[a]); }

    void unite(int a, int b) {
        if (connected(a, b))
            return;
		
        a = find(a);
        b = find(b);
        if (sizes[a] > sizes[b])
            swap(a, b);

        repr[a] = b;
        siz[b] += siz[a];
    }

    bool connected(int a, int b) { return find(a) == find(b); }

    dsu(int n) {
        for(int i = 0; i < n; i++) {
            ancestor.push_back(i);
            sizes.push_back(1);
        }
    }
};

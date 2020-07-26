class DisjointSetUnion {
private:
    vector<int> ancestor_;
    vector<int> sizes_;

public:
    int find(int a) const {
        return (ancestor_[a] == a) ? a : ancestor_[a] = find(ancestor_[a]);
    }

    void unite(int a, int b) {
        if (connected(a, b))
            return;
		
        a = find(a);
        b = find(b);
        if (sizes_[a] > sizes[b])
            swap(a, b);

        ancestor_[a] = b;
        sizes_[b] += sizes_[a];
    }

    inline bool connected(int a, int b) const { return find(a) == find(b); }

    dsu(int n) : sizes(vector<int>(n, 1)) {
        ancestor_.resize(n);
        for (int i = 0; i < n; i++)
            ancestor_[i] = i;
    }
};

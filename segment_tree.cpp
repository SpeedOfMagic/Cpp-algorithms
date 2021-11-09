class SegmentTree {
private:
    const int nothing = -1e9;
    vector<int> val;
    size_t n;

public:
    static inline int op(int a, int b) { return a + b; }

    void update(int pos, int value) {
        size_t cur = val.size() + pos - 1;
        for (val[cur] = value, cur >>= 1; cur; cur >>= 1)
            val[cur] = op(val[cur << 1], val[cur << 1 | 1]);
    }

    int query(int l, int r, int cur, int ll, int rr) {
        if (l > r)
            return nothing;
        if (l == ll && r == rr)
            return val[cur];

        int mid = (ll + rr) >> 1;
        return op(query(l, min(r, mid), cur << 1, ll, mid),
                 query(max(l, mid + 1), r, cur << 1 | 1, mid + 1, rr));
    }

    inline int query(int l, int r) {
        return query(l, r, 1, 1, static_cast<int>(n));
    }

    SegmentTree(size_t _n) {
        for (n = _n; n & (n - 1); n++) {}
        val = vector<int>(n * 2, nothing);
    }

    SegmentTree(const vector<int>& arr) {
        for (n = arr.size(); n & (n - 1); n++) {}
        val = vector<int>(n * 2, nothing);
        for (size_t i = n + arr.size() - 1; i > 0; --i)
            val[i] = ((i < n) ? op(val[i << 1], val[i << 1 | 1]) : arr[i - n]);
    }
};

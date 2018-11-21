struct segTree {
    const int nothing = -1e9;
    vector<int> val;
    int n;

    int f(int a, int b) { return max(a, b); }

    void update(int pos, int value) {
        int cur = 1, l = 1, r = val.size() >> 1;
        while (l != r) {
            int mid = (l + r) / 2;
            if (pos <= mid) {
                cur <<= 1;
                r = mid;
            } else {
                cur = cur << 1 | 1;
                l = mid + 1;
            }
        }
        for (val[cur] = value, cur >>= 1; cur; cur >>= 1)
            val[cur] = f(val[cur << 1], val[cur << 1 | 1]);
    }

    int query(int l, int r, int cur = 1, int ll = 1, int rr = 1e9) {
        rr = min(rr, n);
        if (l > r)
            return nothing;
        if (l == ll && r == rr)
            return val[cur];

        int mid = (ll + rr) >> 1;
        return f(query(l, min(r, mid), cur << 1, ll, mid), query(max(l, mid + 1), r, cur << 1 | 1, mid + 1, rr));
    }

    segTree(vector<int> arr) {
        for (n = arr.size(); n & (n - 1); n++) {}
        val = vector<int>(n * 2, nothing);
        for (int i = n + arr.size() - 1; i; i--)
            val[i] = ((i < n) ? f(val[i << 1], val[i << 1 | 1]) : arr[i - n]);
    }
};
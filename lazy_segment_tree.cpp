struct LazySegmentTree {
	const int nothing = -1e9;
	vector<int> val, lazy;
	int n;

	constexpr int f(int a, int b) { return max(a, b); }

	inline void pushdown(int cur) {
		if (lazy[cur])
			val[cur] = lazy[cur];
		if (cur < n && lazy[cur]) {
			lazy[cur << 1] = lazy[cur];
			lazy[cur << 1 | 1] = lazy[cur];
		}
		lazy[cur] = 0;
	}

	void update(int l, int r, int value, int cur = 1, int ll = 1, int rr = 1e9) {
		rr = min(rr, n);
		pushdown(cur);
		if (l > r)
			return;
		if (l == ll && r == rr) {
			lazy[cur] = value;
			pushdown(cur);
			return;
		}

		int mid = (ll + rr) >> 1;
		update(l, min(r, mid), value, cur << 1, ll, mid);
		update(max(l, mid + 1), r, value, cur << 1 | 1, mid + 1, rr);
		val[cur] = f(val[cur << 1], val[cur << 1 | 1]);
	}

	int query(int l, int r, int cur = 1, int ll = 1, int rr = 1e9) {
		rr = min(rr, n);
		pushdown(cur);
		if (l > r)
			return nothing;
		if (l == ll && r == rr)
			return val[cur];

		int mid = (ll + rr) >> 1;
		return f(query(l, min(r, mid), cur << 1, ll, mid), query(max(l, mid + 1), r, cur << 1 | 1, mid + 1, rr));
	}

	LazySegmentTree(vector<int> arr) {
		for (n = arr.size(); n & (n - 1); n++) {}
		val = vector<int>(n * 2, nothing);
		lazy = vector<int>(n * 2, 0);
		for (int i = n + arr.size() - 1; i; i--)
			val[i] = ((i < n) ? f(val[i << 1], val[i << 1 | 1]) : arr[i - n]);
	}
};

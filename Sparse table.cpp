struct sparseTable {
	int n;
	vector<int> msb; //1 << msb[i] = most significant bit of i
	vector<vector<int>> arr;

	sparseTable(int _n) {
		n = _n;
		msb = vector<int>(n + 1);
		msb[0] = -1;
		for (int i = 1; i <= n; i++)
			msb[i] = ((i & (i - 1)) == 0) + msb[i - 1];
		arr = vector<vector<int>>(n, vector<int>(msb[n] + 1, 0));
	}

	sparseTable(vector<int> a) {
		*this = sparseTable(a.size());
		for (int i = 0; i < n; i++)
			append(i, a[i]);
	}

	int op(int a, int b) { return min(a, b); }

	int query(int l, int r) { //0-indexed, works properly if only append was called
		return op(arr[r][msb[r - l + 1]], arr[(1 << msb[r - l + 1]) + l - 1][msb[r - l + 1]]);
	}

	void append(int pos, int element) {
		//arr[pos] = element; query(l, r) works properly if there were append(pos + 1, a), ..., append(r, z)
		arr[pos][0] = element;
		for (int i = 1; i <= msb[pos + 1]; i++)
			arr[pos][i] = op(arr[pos][i - 1], arr[pos - (1 << (i - 1))][i - 1]);
	}

	void rappend(int pos, int element) {
		//arr[pos] = element; query(l, r) works properly if there were rappend(l, a), ..., rappend(pos - 1, z)
		arr[pos][0] = element;
		for (int i = 1; i <= msb[n - pos]; i++)
			arr[pos][i] = op(arr[pos][i - 1], arr[pos + (1 << (i - 1))][i - 1]);
	}

	int rquery(int l, int r) { //0-indexed, works properly if only rappend was called
		return op(arr[l][msb[r - l + 1]], arr[r - (1 << msb[r - l + 1]) + 1][msb[r - l + 1]]);
	}
};
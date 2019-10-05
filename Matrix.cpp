vector<vector<int>> makeIdMatrix(int n) {
    vector<vector<int>> res(n, vint(n));
	for (size_t i = 0; i < n; ++i)
		for (size_t j = 0; j < n; ++j)
            res[i][j] = (i == j);
    return res;
}

vector<vector<int>> mul(const vector<vector<int>>& a, const vector<vector<int>>& b, int mod = INT_MAX) {
	if (a.empty() || b.empty())
		return {};
	
	assert(a[0].size() == b.size());
    vector<vector<int>> res(a.size(), vector<int>(b[0].size(), 0));
	for (size_t i = 0; i < a.size(); ++i)
		for (size_t j = 0; j < b[0].size(); ++j)
			for (size_t l = 0; l < b.size(); ++l)
                res[i][j] = (res[i][j] + (a[i][l] * b[l][j]) % mod) % mod;

    return res;
}

vector<vector<int>> commute(const vector<vector<int>>& a, const vector<vector<int>>& b) {
	assert(a.size() == a[0].size() && a.size() == b.size() && b.size() == b[0].size());
    vector<vector<int>> r1 = mul(a, b), r2 = mul(b, a);
    for (size_t i = 0; i < a.size(); i++)
        for (size_t j = 0; j < a.size(); ++j)
            r1[i][j] -= r2[i][j];
    return r1;
}

vector<vector<int>> pow(const vector<vector<int>>& a, int k, int mod = INT_MAX) {
    if (k == 0)
        return makeIdMatrix(sz(a));
    else if (k % 2)
        return mul(a, pow(a, k - 1), mod);
    else {
        vector<vector<int>> b = pow(a, k / 2);
        return mul(b, b, mod);
    }
}

istream& operator>>(istream& is, vector<vector<int>>& a) {
	for (size_t i = 0; i < a.size(); ++i)
		for (size_t j = 0; j < a[0].size(); ++j)
			is >> a[i][j];
	return is;
}

ostream& operator<<(ostream& os, const vector<vector<int>>& a) {
	for (size_t i = 0; i < a.size(); ++i) {
		for (size_t j = 0; j < a[0].size(); ++j)
			os << a[i][j] << " ";
		os << endl;
	}
	return os;
}
const int mod = 1e9 + 7;
vector<vector<int>> mul(vector<vector<int>> a, vector<vector<int>> b) {
    int n = sz(a), m = sz(b[0]), k = sz(b);
    vector<vector<int>> res(n, vint(m, 0));
    rep(i, 0, n)
        rep(j, 0, m)
            rep(l, 0, k)
                res[i][j] = (res[i][j] + (a[i][l] * b[l][j]) % mod) % mod;

    return res;
}

vector<vector<int>> makeIdMatrix(int n) {
    vector<vector<int>> res(n, vint(n));
    rep(i, 0, n)
        rep(j, 0, n)
            res[i][j] = (i == j);
    return res;
}

vector<vector<int>> pow(vector<vector<int>> a, int k) {
    if (k == 0)
        return makeIdMatrix(sz(a));
    else if (k % 2)
        return mul(a, pow(a, k - 1));
    else {
        vector<vector<int>> b = pow(a, k / 2);
        return mul(b, b);
    }
}
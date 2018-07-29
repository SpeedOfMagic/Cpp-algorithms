const int N = 100000; //set me
const int K = 20; //set me
int dp[N][K];

int cost(int l, int r) { //implement me

}

int solve(int i, int j, int l, int r) {
    int res = inf;
    int p = 0;

    for (int k = l; k <= min(i - 1, r); k++) {
        int pos = dp[k][j - 1] + cost(k + 1, i);
        if (pos < res) {
            res = pos;
            p = k;
        }
    }

    dp[i][j] = res;
    return p;
}

void calc(int j, int a, int b, int x, int y) {
    if (a > b)
        return;

    int z = (a + b) / 2;
    int p = solve(z, j, x, y);

    calc(j, a, z - 1, x, p);
    calc(j, z + 1, b, p, y);
}

int makeDP(int n, int k) {
    for (int i = 0; i < n; i++)
        dp[i][0] = cost(0, i);

    for (int j = 1; j < k; j++)
        calc(j, 0, n - 1, 0, n - 1);

    return dp[n - 1][k - 1];
}
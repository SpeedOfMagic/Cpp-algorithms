const int N = 1e5 + 1;

vector<int> g[N]; //init me
int height[N];

const int M = 20;
int kthAncestor[N][M];

void precalc(int cur, int h = 0, int p = -1) {
    height[cur] = h;

    if (p != -1) {
        for (int j = 0; j < M; j++)
            kthAncestor[cur][j] = -1;

        kthAncestor[cur][0] = p;
        int pos = p;
        int k = 0;
        while (kthAncestor[pos][k] != -1) {
            kthAncestor[cur][k + 1] = kthAncestor[pos][k];
            pos = kthAncestor[pos][k];
            k++;
        }
    }

    for (int i : g[cur])
        if (i != p)
            precalc(i, h + 1, cur);
}

int lca(int v, int u) {
    if (height[v] > height[u])
        swap(v, u);
    int d = height[u] - height[v];

    int k = 0;
    while (d) {
        if (d & 1)
            u = kthAncestor[u][k];
        d >>= 1;
        k++;
    }

    k = M - 1;

    while (v != u)
        if (kthAncestor[v][k] != kthAncestor[u][k] || k == 0) {
            v = kthAncestor[v][k];
            u = kthAncestor[u][k];
        } else
            k--;

    return v;
}

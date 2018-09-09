const int N = 1e5 + 1;

vector<int> g[N]; //init me
int height[N];

const int M = 20;
int kthAncestor[N][M];

void calc(int cur, int p) {
    height[cur] = ((p == -1) ? 0 : height[p] + 1);

    for (int j = 0; j < M; j++)
        kthAncestor[cur][j] = -1;
    if (p != -1) {
        kthAncestor[cur][0] = p;
        int pos = p;
        int k = 0;
        while (kthAncestor[pos][k] != -1) {
            kthAncestor[cur][k + 1] = kthAncestor[pos][k];
            pos = kthAncestor[pos][k];
            k++;
        }
    }
}

void precalc(int cur, int p = -1) {
	calc(cur, p);
	for (int i : g[cur])
        if (i != p)
            precalc(i, cur);
}

int getKthAncestor(int v, unsigned int distance) {
    int k = 0;
    while (distance && k < M) {
        if (distance & 1)
            v = kthAncestor[v][k];
        distance >>= 1;
        k++;
    }

    return v;
}

int lca(int v, int u) {
    if (height[v] > height[u])
        swap(v, u);

    int d = height[u] - height[v];

    u = getKthAncestor(u, d);

    int k = M - 1;

    while (v != u)
        if (kthAncestor[v][k] != kthAncestor[u][k] || k == 0) {
            v = kthAncestor[v][k];
            u = kthAncestor[u][k];
        } else
            k--;

    return v;
}

int distance(int v, int u, int theirLCA = -1) {
	return height[v] + height[u] - 2 * height[(theirLCA == -1) ? lca(v, u) : theirLCA];
}

bool isAncestor(int posAncestor, int v) {
	return (getKthAncestor(v, height[v] - height[posAncestor]) == posAncestor);
}

const int N = 1e5 + 1;
vector<int> t[N]; //init me

int h[N];
const int M = 17;
vector<vector<int>> kthAncestor(N, vector<int>(M, -1));
inline void precalc(int cur = 1, int p = -1) {
    h[cur] = (p != -1) ? (h[p] + 1) : 0;
    for (int k = 0, d = p; d != -1; k++) {
        kthAncestor[cur][k] = d;
        d = kthAncestor[d][k];
    }

    for (int i : t[cur])
        if (i != p)
            precalc(i, cur);
}

inline int lca(int v, int u) {
    if (h[v] > h[u])
        swap(v, u);

    for (int k = 0, d = h[u] - h[v]; d; k++, d >>= 1)
        if (d & 1)
            u = kthAncestor[u][k];

    for (int k = M - 1; u != v;)
        if (kthAncestor[u][k] != kthAncestor[v][k] || !k) {
            u = kthAncestor[u][k];
            v = kthAncestor[v][k];
        } else
            k--;
    return u;
}

int dist(int v, int u) { return h[v] + h[u] - 2 * h[lca(v, u)]; }

int getKthAncestor(int v, unsigned int distance) {
    for (int k = 0; distance && k < M; k++, distance >>= 1)
        if (distance & 1)
            v = kthAncestor[v][k];
    return v;
}

inline bool isAncestor(int posAncestor, int v) {
    if (h[v] < h[posAncestor])
        return 0;
    return getKthAncestor(v, h[v] - h[posAncestor]) == posAncestor;
}

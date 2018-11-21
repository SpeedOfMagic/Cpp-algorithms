const int N = 1e5 + 1;
vector<int> g[N];
char vis[N];
set<int> g2Rev[N];
int col[N];
stack<int> l;
int curColor = -1;
void kosarajuLike(int cur, bool todo) {
    if (todo) {
        col[cur] = curColor;
        for (int i : g2Rev[cur])
            if (col[i] == -1)
                kosarajuLike(i, todo);
    } else {
        vis[cur] = 1;
        for (int i : g[cur]) {
            if (!g2Rev[cur].count(i))
                g2Rev[i].insert(cur);
            if (!vis[i])
                kosarajuLike(i, todo);
        }
        l.push(cur);
    }
}
vector<int> condensation[N];
void makeCondensation(vector<pair<int, int>> edges) {
    memset(vis, 0, sizeof vis);
    memset(col, -1, sizeof col);
    for (int i = 1; i < N; i++)
        if (!vis[i])
            kosarajuLike(i, 0);

    while (!l.empty()) {
        if (col[l.top()] == 0) {
            curColor++;
            kosarajuLike(l.top(), 1);
        }
        l.pop();
    }
    for (auto edge : edges) {
        int i = col[edge.first], j = col[edge.second];
        if (i != j) {
            condensation[i].push_back(j);
            condensation[j].push_back(i);
        }
    }
}
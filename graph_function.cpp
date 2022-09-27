using Graph = vector<multiset<int>>;
using Tree = Graph;

Graph ReadSimpleGraph(bool start_from_one = true, bool oriented = false) {
    int n, m;
    cin >> n >> m;
    Graph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (start_from_one) {
            --u; --v;
        }
        g[u].insert(v);
        if (!oriented) {
            g[v].insert(u);
        }
    }
    return g;
}

struct PathGetter {
    const Graph& g_;

    PathGetter(const Graph& g) : g_(g) {}

    vector<int> path;
    vector<char> visited;

    bool DFS(int cur, int need) {
        path.push_back(cur);
        visited[cur] = true;
        if (cur == need) {
            return true;
        }
        for (int nxt : g_[cur]) {
            if (!visited[nxt]) {
                if (DFS(nxt, need)) {
                    return true;
                }
            }
        }
        path.pop_back();
        return false;
    }

    vector<int> GetPath(int u, int v) {
        path.clear();
        visited.assign(g_.size(), 0);
        DFS(u, v);
        return path;
    }
};

struct DistanceCalculator {
    const Graph& g_;

    DistanceCalculator(const Graph& g) : g_(g) {}

    vector<int> dist;
    vector<char> visited;

    void DFS(int cur, int par, int len) {
        dist[cur] = len;
        for (int nxt : g_[cur]) {
            if (nxt != par) {
                DFS(nxt, cur, len + 1);
            }
        }
    }

    vector<int> CalculateDistanceFrom(int v) {
        dist.assign(g_.size(), 0);
        visited.assign(g_.size(), 0);
        DFS(v, -1, 0);
        return dist;
    }
};

bool IsBipartite(const Graph& g, vector<char>* ans_color = nullptr) {
    vector<char> color(g.size(), -1);
    for (size_t to_check = 0; to_check < g.size(); ++to_check) {
        if (color[to_check] == -1) {
            color[to_check] = 0;
            queue<int> bfs;
            bfs.push(to_check);
            while (!bfs.empty()) {
                int cur = bfs.front();
                bfs.pop();
                for (int nxt : g[cur]) {
                    if (color[nxt] == color[cur]) {
                        return false;
                    }
                    if (color[nxt] == -1) {
                        color[nxt] = 1 - color[cur];
                        bfs.push(nxt);
                    }
                }
            }
        }
    }
    if (ans_color != nullptr) {
        *ans_color = std::move(color);
    }
    return true;
}

bool IsConnected(const Graph& g) {
    vector<char> visited(g.size(), false);
    queue<int> bfs;
    bfs.push(0);
    visited[0] = true;
    while (!bfs.empty()) {
        int cur = bfs.front();
        bfs.pop();
        for (int nxt : g[cur]) {
            if (!visited[nxt]) {
                visited[nxt] = true;
                bfs.push(nxt);
            }
        }
    }
    for (size_t i = 0; i < g.size(); ++i) {
        if (!visited[i]) {
            return false;
        }
    }
    return true;
}

vector<int> GetEulerCycle(Graph g) {
    for (size_t i = 0; i < g.size(); ++i) {
        if (g[i].size() % 2) {
            return {};
        }
    }

    vector<int> ans;
    stack<int> dfs;
    dfs.push(0);
    while (!dfs.empty()) {
        int cur = dfs.top();
        if (g[cur].empty()) {
            dfs.pop();
            ans.push_back(cur);
        } else {
            int nxt = *g[cur].begin();
            g[cur].erase(g[cur].find(nxt));
            g[nxt].erase(g[nxt].find(cur));
            dfs.push(nxt);
        }
    }
    return ans;
}

vector<int> GetEulerCycleOriented(Graph g) {
    vector<size_t> incoming(g.size(), 0);
    for (size_t i = 0; i < g.size(); ++i) {
        for (int nxt : g[i]) {
            ++incoming[nxt];
        }
    }
    for (size_t i = 0; i < g.size(); ++i) {
        if (incoming[i] != g[i].size()) {
            return {};
        }
    }

    vector<int> ans;
    stack<int> dfs;
    dfs.push(0);
    while (!dfs.empty()) {
        int cur = dfs.top();
        if (g[cur].empty()) {
            dfs.pop();
            ans.push_back(cur);
        } else {
            int nxt = *g[cur].begin();
            g[cur].erase(g[cur].find(nxt));
            dfs.push(nxt);
        }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
}

vector<int> GetEulerPathOriented(Graph g) {
    vector<size_t> incoming(g.size(), 0);
    for (size_t i = 0; i < g.size(); ++i) {
        for (int nxt : g[i]) {
            ++incoming[nxt];
        }
    }
    int start = -1, finish = -1;
    for (size_t i = 0; i < g.size(); ++i) {
        if (incoming[i] != g[i].size()) {
            if (incoming[i] < g[i].size() && start == -1) {
                start = static_cast<int>(i);
            } else if (incoming[i] > g[i].size() && finish == -1) {
                finish = static_cast<int>(i);
            } else {
                return {};
            }
        }
    }
    if (start == -1 || finish == -1) {
        return {};
    }
    g[finish].insert(start);
    
    vector<int> cycle = GetEulerCycleOriented(g);
    if (cycle.empty()) {
        return {};
    }
    cycle.pop_back();
    for (size_t i = 1; i < cycle.size(); ++i) {
        if (cycle[i - 1] == finish && cycle[i] == start) {
            std::rotate(cycle.begin(), cycle.begin() + i, cycle.end());
            break;
        }
    }
    return cycle;
}

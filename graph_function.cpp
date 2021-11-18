using Graph = vector<vector<int>>;
using Tree = Graph;

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

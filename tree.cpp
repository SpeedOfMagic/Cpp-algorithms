using Tree = vector<vector<int>>;
using Edge = pair<int, int>;

struct DiamResult {
    int len;
    int u, v;
};

class TreeDiameter {
private:
    const Tree& tree_;

    pair<int, int> FindFarthest(int cur, int par, int len) {
        pair<int, int> res = { len, cur };
        for (int nxt : tree_[cur]) {
            if (nxt != par) {
                res = max(res, FindFarthest(nxt, cur, len + 1));
            }
        }
        return res;
    }

public:
    TreeDiameter(const Tree& tree) : tree_(tree) {}

    DiamResult GetDiam() {
        int u = FindFarthest(1, -1, 0).second;
        pair<int, int> res = FindFarthest(u, -1, 0);
        return { res.first, u, res.second };
    }
};

class TreePath {
private:
    const Tree& tree_;

    bool GetPathRecursive(int cur, int to, int par, vector<Edge>& cur_edges) {
        if (cur == to) {
            return true;
        }
        for (int nxt : tree_[cur]) if (nxt != par) {
            cur_edges.push_back({ cur, nxt });
            if (GetPathRecursive(nxt, to, cur, cur_edges)) {
                return true;
            }
            cur_edges.pop_back();
        }
        return false;
    }

public:
    TreePath(const Tree& tree) : tree_(tree) {}

    vector<Edge> GetPath(int from, int to) {
        vector<Edge> cur_edges;
        GetPathRecursive(from, to, -1, cur_edges);
        return cur_edges;
    }
};
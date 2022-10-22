using Graph = vector<vector<int>>;

// Complexity of CalcMatchingSize (Kuhn algorithm): O(nm), but in reality it's faster
class KuhnMatching {
private:
    const Graph& g;
    vector<int> matched;
    vector<char> used;
 
    bool TryKuhn(int v) {
        if (used[v])  return false;
        used[v] = true;
        for (int to : g[v]) {
			// If matched[to] == -1, then we can use it
			// Otherwise we try to find matching for vertex it's currently matched to
            if (matched[to] == -1 || TryKuhn(matched[to])) {
                matched[to] = v;
                return true;
            }
        }
        return false;
    }
 
public:
    // g must contain only first part
    KuhnMatching(const Graph& g_, int secondPartSize)
    : g(g_)
    , matched(vector<int>(secondPartSize, -1))
    , used(vector<char>(g.size(), false))
    {}
 
	// If zeroIfNotPerfect is set, answer is 0 or perfect matching size, but it also speeds up code 
    int CalcMatchingSize(bool zeroIfNotPerfect = false) {
        int ans = 0;
 
        // Approximate matching to speed up Kuhn
        vector<char> usedFirstPart(g.size(), false);
        for (size_t v = 0; v < g.size(); ++v) {
            for (int to : g[v]) {
                if (matched[to] == -1) {
                    ++ans;
                    matched[to] = v;
                    usedFirstPart[v] = true;
                    break;
                }
            }
        }
 
        for (size_t i = 0; i < g.size(); ++i) {
            if (usedFirstPart[i]) {
                continue;
            }
            if (TryKuhn(i)) {
                ++ans;
                used.assign(used.size(), false);
            } else {
                if (zeroIfNotPerfect) {
                    return 0;
                }
            }
        }
        return ans;
    }
 
	// If noneIfNotPerfect is set, answer is {} or perfect matching, but it also speeds up code
    vector<pair<int, int>> CalcMatching(bool noneIfNotPerfect = false) {
        vector<pair<int, int>> matching;
        matching.reserve(CalcMatchingSize(noneIfNotPerfect));
        if (matching.capacity() == 0) {
            return matching;
        }
 
        for (size_t i = 0; i < matched.size(); ++i) {
            if (matched[i] != -1) {
                matching.emplace_back(matched[i], i);
            }
        }
        return matching;
    }
};

// Most of the code was used here: https://gist.github.com/Chillee/ad2110fc17af453fb6fc3357a78cfd28
// I rewrote some things to support initialization and removed non-scaling
// Complexity of calc(): O(nm log U), where U = 2^30
template <class T = int> struct Dinic {
    int lim = 1;
    const T INF = numeric_limits<T>::max();
    struct edge {
        int to, rev;
        T cap, flow;
    };

    int s, t;
    vector<int> level;
    vector<uint32_t> ptr;
    vector<vector<edge>> adj;

    Dinic(int n, int s, int t)
    : s(s)
    , t(t)
    , level(vector<int>(n))
    , ptr(vector<uint32_t>(n))
    , adj(vector<vector<edge>>(n))
    {} 

    void addEdge(int a, int b, T cap, bool isDirected = true) {
        adj[a].push_back({b, int(adj[b].size()), cap, 0});
        adj[b].push_back({a, int(adj[a].size()) - 1, isDirected ? 0 : cap, 0});
    }
    bool bfs() {
        queue<int> q({s});
        level.assign(level.size(), -1);
        level[s] = 0;
        while (!q.empty() && level[t] == -1) {
            int v = q.front();
            q.pop();
            for (auto e : adj[v]) {
                if (level[e.to] == -1 && e.flow < e.cap && e.cap - e.flow >= lim) {
                    q.push(e.to);
                    level[e.to] = level[v] + 1;
                }
            }
        }
        return level[t] != -1;
    }
    T dfs(int v, T flow) {
        if (v == t || !flow)
            return flow;
        for (; ptr[v] < adj[v].size(); ptr[v]++) {
            edge &e = adj[v][ptr[v]];
            if (level[e.to] != level[v] + 1)
                continue;
            if (T pushed = dfs(e.to, min(flow, e.cap - e.flow))) {
                e.flow += pushed;
                adj[e.to][e.rev].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    long long calc() {
        long long flow = 0;
        for (lim = (1 << 30); lim > 0; lim >>= 1) {
            while (bfs()) {
                ptr.assign(ptr.size(), 0);
                while (T pushed = dfs(s, INF))
                    flow += pushed;
            }
        }
        return flow;
    }
};

// Complexity: O(n^2m^2)
vector<pair<int, int>> MinCut(int n, const vector<pair<int, int>>& edges) {
    Dinic d(n, 0, n - 1);
    for (pair<int, int> e : edges) {
        d.addEdge(e.first, e.second, 1, false);
    }
    int ans = d.calc();

    vector<pair<int, int>> ans_e, cur_e;
    for (size_t i = 0; i < edges.size(); ++i) {
        Dinic d2(n, 0, n - 1);
        for (pair<int, int> e : cur_e) {
            d2.addEdge(e.first, e.second, 1, false);
        }
        for (size_t j = i + 1; j < edges.size(); ++j) {
            d2.addEdge(edges[j].first, edges[j].second, 1, false);
        }
        int pos = d2.calc();
        if (ans > pos) {
            ans_e.push_back(edges[i]);
            --ans;
        } else {
            cur_e.push_back(edges[i]);
        }
    }
    return ans_e;
}

// Vertexes of second part must be distinct from vertexes in the first part
// n - all vertexes from first and second part
// Complexity: O(m * sqrt(n))
vector<pair<int, int>> DinicMatching(int n, const vector<pair<int, int>>& edges) {
    const int start = n, finish = n + 1;
    Dinic<> d(n + 2, start, finish);
    set<int> first_part, second_part;
    for (pair<int, int> e : edges) {
        first_part.insert(e.first);
        second_part.insert(e.second);
        d.addEdge(e.first, e.second, 1);
    }
    for (int v : first_part) {
        d.addEdge(start, v, 1);
    }
    for (int v : second_part) {
        d.addEdge(v, finish, 1);
    }
    size_t matching_size = d.calc();
    vector<pair<int, int>> ans;
    ans.reserve(matching_size);
    for (int i = 0; i < n; ++i) {
        for (const auto& e : d.adj[i]) {
            if (e.to != finish && e.flow == 1) {
                ans.emplace_back(i, e.to);
            }
        }
    }
    assert(matching_size == ans.size());
    return ans;
}
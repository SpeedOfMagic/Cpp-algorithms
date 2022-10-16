using Graph = vector<vector<int>>;

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

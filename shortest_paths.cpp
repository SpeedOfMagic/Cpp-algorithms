using WeightedGraph = vector<vector<pair<int, long long>>>;

WeightedGraph ReadWeightedGraph(bool start_from_one = true, bool oriented = false) {
    int n, m;
    cin >> n >> m;
    WeightedGraph g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        long long c;
        cin >> u >> v >> c;
        if (start_from_one) {
            --u; --v;
        }
        g[u].emplace_back(v, c);
        if (!oriented) {
            g[v].emplace_back(u, c);
        }
    }
    return g;
}

vector<long long> DijkstraWeightedEdge(const WeightedGraph& g, int start) {
    vector<long long> res(g.size(), INT64_MAX);
	res[start] = 0;
	
    priority_queue<pair<long long, int>> nxt;
    nxt.push({-res[start], start});

    while (!nxt.empty()) {
        int cur = nxt.top().second;
        long long cost = -nxt.top().first;
        nxt.pop();
        if (cost != res[cur])
            continue;

        for (pair<int, long long> nxt_weight : g[cur]) {
            if (res[nxt_weight.first] > cost + nxt_weight.second) {
                res[nxt_weight.first] = cost + nxt_weight.second;
                nxt.push({-res[nxt_weight.first], nxt_weight.first});
            }
        }
    }
    return res;
}

using Matrix = vector<vector<long long>>;

Matrix FloydWarshall(Matrix g) {
    for (size_t t = 0; t < g.size(); ++t) {
        for (size_t from = 0; from < g.size(); ++from) {
            for (size_t to = 0; to < g.size(); ++to) {
                g[from][to] = min(g[from][to], g[from][t] + g[t][to]);
            }
        }
    }
    return g;
}

const int N = 1e5 + 1;
vector<int> g[N]; //init me
vector<int> weight[N]; //init me

vector<int> dijkstra(int st) {
    vector<int> res(N, inf);
    priority_queue<pair<int, int>> nxt;
    nxt.push({weight[st], d});

    while (!nxt.empty()) {
        int cur = nxt.top().second;
        int cost = -nxt.top().first;
        nxt.pop();
        if (cost != res[cur])
            continue;

        for (int i : g[cur])
            if (res[i] > cost + weight[i]) {
                res[i] = cost + weight[i];
                nxt.push({-res[i], i});
            }
    }

    return res;
}
const int N = 1e5 + 1;
vector<int> g[N]; //init me
int weight[N]; //init me

vector<int> dijkstra(int st) {
    vector<int> res(N, inf);
	res[st] = weight[st];
	
    priority_queue<pair<int, int>> nxt;
    nxt.push({-weight[st], st});

    while (!nxt.empty()) {
        int cost = -nxt.top().first;
        int cur = nxt.top().second;
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
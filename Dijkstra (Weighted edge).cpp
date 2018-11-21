const int N = 1e5 + 1;
vector<pair<int, int>> g[N]; //init me

vector<int> dijkstra(int st) {
    vector<int> res(N, inf);
	res[st] = 0;
	
    priority_queue<pair<int, int>> nxt;
    nxt.push({-res[st], st});

    while (!nxt.empty()) {
        int cur = nxt.top().second;
        int cost = -nxt.top().first;
        nxt.pop();
        if (cost != res[cur])
            continue;

        for (pair<int, int> i : g[cur])
            if (res[i.first] > cost + i.second) {
                res[i.first] = cost + i.second;
                nxt.push({-res[i.first], i.first});
            }
    }

    return res;
}
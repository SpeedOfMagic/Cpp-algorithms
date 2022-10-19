using SetGraph = vector<multiset<int>>;

vector<int> GetEulerCycle(SetGraph g) {
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

vector<int> GetEulerCycleOriented(SetGraph g) {
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

vector<int> GetEulerPathOriented(SetGraph g) {
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

const int N = 1e5 + 1;
vector<int> g[N]; //init me

set<int> g2Rev[N];
bool vis[N];
int col[N];
stack<int> l;
int curColor = -1;

void kosarajuLike(int cur, bool todo) {
    if(todo){
        col[cur] = curColor;
        for(int i : g2Rev[cur])
            if(col[i] == -1)
                kosarajuLike(i, todo);
    } else {
        vis[cur] = 1;
        for (int i : g[cur]) {
            if(!g2Rev[cur].count(i))
                g2Rev[i].insert(cur);

            if(!vis[i])
                kosarajuLike(i, todo);
        }
        l.push(cur);
    }

}

vector<int> condensation[N];

void makeCondensation(vector<pair<int, int>> E) { //E - edges of a graph
    for (int i = 0; i < N; i++) {
        vis[i] = 0;
        col[i] = -1;
    }

	for (int i = 0; i < N; i++)
        if (!vis[i])
            kosarajuLike(i, 0);

    while(!l.empty()) {
        if(col[l.top()] == 0) {
            curColor++;
            kosarajuLike(l.top(), 1);
        }

        l.pop();
    }

    for (auto edge : E) {
        int i = edge.first, j = edge.second;
        if(col[i] == col[j])
            continue;

        condensation[col[i]].push_back(col[j]);
        condensation[col[j]].push_back(col[i]);
    }
}
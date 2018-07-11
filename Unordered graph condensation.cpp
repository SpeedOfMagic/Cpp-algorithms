const int N = 5e5 + 1;
vector<int> g[N]; //init me

set<int> g2Rev[N];
bool vis[N];
int col[N];
stack<int> l;
int color = 0;

void korasajuLike(int cur, bool todo) {
    if(todo){
        col[cur] = color;
        for(int i : g2Rev[cur])
            if(col[i] == 0)
                korasajuLike(i, todo);
    } else {
        vis[cur] = 1;
        for (int i : g[cur]) {
            if(!g2Rev[cur].count(i))
                g2Rev[i].insert(cur);

            if(!vis[i])
                korasajuLike(i, todo);
        }
        l.push(cur);
    }

}

vint condensation[N];

void makeCondensation(v<pair<int, int>> E) { //E - edges of a graph
    for (int i = 0; i < N; i++) {
        vis[i] = 0;
        col[i] = 0;
    }

    korasajuLike(1, 0);

    while(!l.empty()) {
        if(col[l.top()] == 0) {
            color++;
            korasajuLike(l.top(), 1);
        }
        
        l.pop();
    }

    for (auto edge : E) {
        int i = edge.first, j = edge.second;
        if(col[i] == col[j])
            continue;

        condensation[col[i]].pb(col[j]);
        condensation[col[j]].pb(col[i]);
    }
}

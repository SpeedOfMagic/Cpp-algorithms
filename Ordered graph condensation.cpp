const int N = 1e5 + 1;
vector<int> g[N]; //init me

vector<int> rev[N];
bool vis[N];
int color[N];
int curColor = -1;

stack<int> l;

void kosaraju(int cur, bool todo) {
    if (todo) {
        color[cur] = curColor;
        for (int i : rev[cur])
            if (color[i] == -1)
                kosaraju(i, 1);
    } else {
        vis[cur] = 1;
        for (int i : g[cur])
            if (!vis[i])
                kosaraju(i, 0);

        l.push(cur);
    }
}


vector<int> condensation[N];

void makeCondensation() {
	for (int i = 0; i < N; i++)
		for (int j : g[i])
			rev[j].push_back(i);
	
	for (int i = 0; i < N; i++) {
        vis[i] = 0;
        color[i] = -1;
    }

    for (int i = 0; i < N; i++)
        if (!vis[i])
            kosaraju(i, 0);

    while (!l.empty()) {
        if (color[l.top()] == 0) {
            curColor++;
            kosaraju(l.top(), 1);
        }
		
        l.pop();
    }
    curColor++;

    for (int i = 0; i < N; i++)
        for (int j : g[i])
            if (color[i] != color[j])
                condensation[color[i]].pb(color[j]);
}
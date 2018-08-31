struct dsu {
    vector<int> repr;
    vector<int> siz;

    int _find(int a) {
        if (repr[a] == a)
            return a;
        else
            return repr[a] = _find(repr[a]);
    }

    void unite(int a, int b) {
		if (connected(a, b))
			return;
		
        a = _find(a);
        b = _find(b);
		
        if (siz[a] > siz[b])
            swap(a, b);

        repr[a] = b;

        siz[b] += siz[a];
    }

    bool connected(int a, int b) {
        return _find(a) == _find(b);
    }

    dsu(int n) {
        for(int i = 0; i < n; i++) {
            repr.push_back(i);
            siz.push_back(1);
        }
    }
};

//uses DSU
vector<vector<int>> kruskal(vector<vector<int>>& edges) {
	int m = edges.size();
	vector<vector<int>> E(m);
	
	int n = -1;
	
	for (int i = 0; i < m; i++) {
		E[i][0] = edges[i][2];
		E[i][1] = edges[i][0];
		E[i][2] = edges[i][1];
		n = max(n, max(edges[i][0], edges[i][1]));
	}
			
	sort(E, E + m);
	
	dsu d(n);
	
	vector<vector<int>> res;
	for (int i = 0; i < m; i++)
		if (!d.connected(E[i][1], E[i][2])) {
            res.push_back({E[i][1], E[i][2], E[i][0]});
            d.unite(E[i][1], E[i][2]);
        }
		
	return res;
}
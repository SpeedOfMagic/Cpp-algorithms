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

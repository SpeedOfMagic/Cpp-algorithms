const int N = 1e5 + 1;
vector<int> t[N]; //init me
int siz[N];
bitset<N> added;

int calcSize(int cur, int p) {
    siz[cur] = 1;
    for (int i : t[cur])
        if (!added.test(i) && i != p)
            siz[cur] += calcSize(i, cur);
    return siz[cur];
}

void solve(int cur) { //implement me

}

void find_centroid(int cur) {
    int lim = calcSize(cur, -1) / 2;
    int pr = -1;
    for (bool again = 1; again;) {
        again = 0;
        for (auto i : t[cur]) 
			if (!added.test(i) && i != pr && siz[i] > lim) {
                pr = cur;
				cur = i;
                again = 1;
                break;
            }
    }
    added.set(cur);
    solve(cur);
	
    for (int i : t[cur])
        if (!added.test(i))
            find_centroid(i);
}
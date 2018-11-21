const int N = 3e5;
deque<int> cycles[N];
int bw = 0;
vector<int> eulerianTrail;
int n;
set<int> g[N];

void makeAnswer(int cur) {
    eulerianTrail.push_back(cur);
	if (!cycles[cur].empty()) {
        while (!cycles[cur].empty()){
            int a = cycles[cur].front();
            cycles[cur].pop_front();
            makeAnswer(a);
        }
        eulerianTrail.push_back(cur);
	}
}

void makeEulerianTrail() {
	vector<int> odd;
	for (int i = 0; i < n; i++)
		if (g[i].size() % 2)
			odd.push_back(i);

	if (odd.size() == 0 || odd.size() == 2){
		if (odd.size()) {
			g[odd[0]].insert(odd[1]);
			g[odd[1]].insert(odd[0]);
			bw = odd[0];
		}
		for (int i = bw; i != (bw ? bw : n) - 1; i = (i + 1) % n) {
			int te = i, p = i;
			for (int j : g[te])
				if (j != p) {
					te = j;
					break;
				}

			if (i == bw && odd.size())
				te = odd[1];
			while (te != i) {
				g[te].erase(p);
				g[p].erase(te);
				if (i == bw && odd.size())
					cycles[i].push_front(te);
				else
                    cycles[i].push_back(te);
				for (int j : g[te])
					if (j != p) {
						p = te;
						te = j;
						break;
					}
			}
			g[te].erase(p);
			g[p].erase(te);
		}
		makeAnswer(bw);
	} else //trail doesn't exist
		eulerianTrail = vector<int>();
}
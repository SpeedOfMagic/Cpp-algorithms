const int R = 1000, C = 1000;
int n, m; //init me

bool valid(int r, int c) { return r >= 0 && r <= n - 1 && c >= 0 && c <= m - 1; }

v<pair<int, int>> neighbours(int r, int c, bool sideOnly = 1) {
    v<pair<int, int>> res;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (sideOnly && ((i != 0) ^ (j != 0)) && valid(r + i, c + j))
                res.pb({r + i, c + j});
            else if (!sideOnly && ((i != 0) || (j != 0)) && valid(r + i, c + j))
                res.pb({r + i, c + j});

    return res;
}

int getHash(int r, int c) { return r * m + c; }

vector<int> g[R * C];
void makeGraph(vector<vector<int>> grid) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (grid[i][j]) {
                g[getHash(i, j)].clear();
                for (auto k : neighbours(i, j))
                    if (grid[i][j] == grid[k.fs][k.sc])
                        g[getHash(i, j)].pb(getHash(k.fs, k.sc));
            }
}

pair<int, int> getCoordinate(int vertexNumber) { return {vertexNumber / m, vertexNumber % m}; }

vector<vector<int>> rotate(vector<vector<int>> grid) {
	int nn = grid.size();
    vector<vector<int>> res(nn, vector<int>(nn));
    for (int i = 0; i < nn / 2 + nn % 2; i++) {
        int cr = i, cc = i, pr = i, pc = nn - i - 1;
		for (int z = 0; z < 4; z++) {
			for (int j = 0; j < nn - i * 2 - 1; j++) {
				res[cr][cc] = grid[pr][pc];
				if (z == 0) {
					cc++;
					pr++;
				} else if (z == 1) {
					cr++;
					pc--;
				} else if (z == 2) {
					cc--;
					pr--;
				} else {
					cr--;
					pc++;
				}
			}
			res[cr][cc] = grid[pr][pc];
		}
    }
    return res;
}

void dropdown(vector<vector<int>> grid) {
    for (int j = 0; j < m; j++) {
        int p = n - 1;
        for (int i = n - 1; i >= 0; i--)
            if (grid[i][j]) {
                int v = grid[i][j];
                grid[i][j] = 0;
                grid[p--][j] = v;
            }
    }
}
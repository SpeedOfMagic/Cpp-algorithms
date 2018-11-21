const int R = 1000;
const int C = 1000;

int n; //init me
int m; //init me

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

int getVertexNumber(int r, int c) { return r * m + c; }

pair<int, int> getCoordinate(int vertexNumber) { return {vertexNumber / m, vertexNumber % m}; }

vector<vector<int>> rotate(vector<vector<int>> grid) {
    vector<vector<int>> res(n, vint(n));
    for (int i = 0; i < n / 2 + n % 2; i++) {
        int cr = i, cc = i, pr = i, pc = n - i - 1;
		for (int z = 0; z < 4; z++) {
			for (int j = 0; j < n - i * 2 - 1; j++) {
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
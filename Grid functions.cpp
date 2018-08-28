const int R = 1000;
const int C = 1000;

int n; //init me
int m; //init me

bool valid(int r, int c) {
    return r >= 0 && r <= n - 1 && c >= 0 && c <= m - 1;
}

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

int getVertexNumber(int r, int c) {
    return r * m + c;
}

pair<int, int> getCoordinate(int vertexNumber) {
    return {vertexNumber / m, vertexNumber % m};
}

v<vint> rotate(v<vint> grid) {
    v<vint> res(n, vint(n));
    for (int i = 0; i < n / 2 + n % 2; i++) {
        int cr = i, cc = i, pr = i, pc = n - i - 1;
        for (int j = 0; j < n - i * 2 - 1; j++) {
            res[cr][cc] = grid[pr][pc];
            cc++;
            pr++;
            //debug(cr, cc, pr, pc);
        }
        res[cr][cc] = grid[pr][pc];

        for (int j = 0; j < n - i * 2 - 1; j++) {
            res[cr][cc] = grid[pr][pc];
            cr++;
            pc--;
            //debug(cr, cc, pr, pc);
        }
        res[cr][cc] = grid[pr][pc];

        for (int j = 0; j < n - i * 2 - 1; j++) {
            res[cr][cc] = grid[pr][pc];
            cc--;
            pr--;
            //debug(cr, cc, pr, pc);
        }
        res[cr][cc] = grid[pr][pc];

        for (int j = 0; j < n - i * 2 - 1; j++) {
            res[cr][cc] = grid[pr][pc];
            cr--;
            pc++;
            //debug(cr, cc, pr, pc);
        }
        res[cr][cc] = grid[pr][pc];
    }

    return res;
}
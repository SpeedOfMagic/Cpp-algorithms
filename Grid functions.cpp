
const int N = 1000;
const int M = 1000;
int grid[N][M]; //init me

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
    return r * M + c;
}

pair<int, int> getCoordinate(int vertexNumber) {
    return {vertexNumber / M, vertexNumber % M};
}

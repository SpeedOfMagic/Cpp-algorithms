struct matrix {
    int n;
    int m;
    vector<vector<int>> mat;

    matrix(vector<vector<int>> matr) : n (sz(matr)), m (sz(matr[0])), mat(matr) {}
    matrix(int N, int M) : n(N), m(M) {
        mat = vector<vector<int>> (N);
        for (int i = 0; i < N; i++)
            mat[i] = vector<int>(M, 0);
    }

    matrix operator+(matrix other) {
        assert(this -> n == other.n && this -> m && other.m);

        matrix C = matrix(this -> n, this -> m);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                C.mat[i][j] = this -> mat[i][j] + other.mat[i][j];

        return C;
    }

    matrix operator*(matrix other) {
        matrix C = matrix(this -> n, this -> m);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                for (int k = 0; k < n; k++)
                    C.mat[i][j] += this -> mat[i][k] * other.mat[j][k];

        return C;
    }

    void operator*=(matrix other) {
        (*this) = (*this) * other;
    }
};

matrix makeIdentityMatrix(int n) {
    matrix identityMatrix = matrix(n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            identityMatrix.mat[i][j] = (i == j);

    return identityMatrix;
}

matrix pow(matrix& cur, int k) {
    if (k == 0)
        return makeIdentityMatrix(cur.n);
    else if (k == 1)
        return cur;
    else {
        matrix C = pow(cur, k / 2);
        C *= C;

        if (k % 2)
            C *= cur;

        return C;
    }
}

#include <cassert>
#include <ostream>
#include <utility>
#include <vector>

using std::vector;

template<typename T>
class Matrix {
 private:
    vector<vector<T>> matrix;

 public:
    const vector<T>& operator[](int i) const { return matrix[i]; }
    vector<T>& operator[](int i) { return matrix[i]; }

    Matrix(const vector<vector<T>>& mat) : matrix(mat) {}

    friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& m) {
        auto [rowSize, colSize] = m.size();
        for (size_t i = 0; i < rowSize; ++i) {
            for (size_t j = 0; j < colSize; ++j) {
                if (j != 0)
                    out << "\t";
                out << m[i][j];
            }

            if (i + 1 != rowSize)
                out << "\n";
        }
        return out;
    }

    const std::pair<size_t, size_t> size() const {
        return {matrix.size(), matrix.empty() ? 0 : matrix[0].size()};
    }

    Matrix& operator+=(const Matrix<T>& m) {
        auto [rowSize, colSize] = size();
        for (size_t i = 0; i < rowSize; ++i)
            for (size_t j = 0; j < colSize; ++j)
                (*this)[i][j] += m[i][j];

        return *this;
    }

    Matrix operator+(const Matrix<T>& m) const {
        Matrix res = *this;
        return res += m;
    }

    template<typename U>
    Matrix& operator*=(const U& scalar) {
        auto [rowSize, colSize] = size();
        for (size_t i = 0; i < rowSize; ++i)
            for (size_t j = 0; j < colSize; ++j)
                (*this)[i][j] *= scalar;

        return *this;
    }

    template<typename U>
    Matrix operator*(const U& scalar) const {
        Matrix res = *this;
        return res *= scalar;
    }

    Matrix& transpose() {
        auto [rowSize, colSize] = size();
        if (rowSize > colSize) {
            for (size_t i = 0; i < colSize; ++i)
                matrix[i].resize(rowSize);
            for (size_t i = 0; i < colSize; ++i)
               for (size_t j = 0; j < rowSize; ++j)
                    if (i >= rowSize || j >= colSize || i < j)
                        std::swap(matrix[i][j], matrix[j][i]);
            matrix.resize(colSize);
        } else {
            matrix.resize(colSize, vector<T>(rowSize));
            for (size_t i = 0; i < colSize; ++i)
                for (size_t j = 0; j < rowSize; ++j)
                    if (i >= rowSize || j >= colSize || i < j)
                        std::swap(matrix[i][j], matrix[j][i]);

            for (size_t i = 0; i < rowSize; ++i)
                matrix[i].resize(rowSize);
        }

        return *this;
    }

    Matrix transposed() const {
        Matrix res = *this;
        return res.transpose();
    }

    Matrix& operator*=(const Matrix& other) {
        auto [rowSize, colSize] = size();
        auto [oRowSize, oColSize] = other.size();
        assert(colSize == oRowSize);
        Matrix res(vector<vector<T>>(rowSize, vector<T>(oColSize, 0)));
        for (size_t i = 0; i < rowSize; ++i)
            for (size_t j = 0; j < oColSize; ++j)
                for (size_t k = 0; k < colSize; ++k)
                    res[i][j] += operator[](i)[k] * other[k][j];
        return *this = res;
    }

    Matrix operator*(const Matrix& other) const {
        Matrix res = *this;
        return res *= other;
    }

    class iterator {
     private:
        typename vector<vector<T>>::iterator rowiter, enditer;
        typename vector<T>::iterator coliter;

     public:
        iterator() {}

        iterator(typename vector<vector<T>>::iterator rowiterator,
                 typename vector<vector<T>>::iterator enditerator,
                 typename vector<T>::iterator coliterator)
                : rowiter(rowiterator)
                , enditer(enditerator)
                , coliter(coliterator) {}

        iterator(typename vector<vector<T>>::iterator rowiterator,
                 typename vector<vector<T>>::iterator enditerator)
                : rowiter(rowiterator)
                , enditer(enditerator) {}

        bool operator==(const iterator& other) const {
            return (rowiter == other.rowiter) && (rowiter == enditer || coliter == other.coliter);
        }
        bool operator!=(const iterator& other) const { return !operator==(other); }

        T& operator*() { return *coliter; }
        iterator& operator++() {
            if (rowiter == enditer) return *this;
            ++coliter;
            if (coliter == (*rowiter).end() && ++rowiter != enditer)
                coliter = (*rowiter).begin();
            return *this;
        }
    };

    iterator begin() {
        if (matrix.size() == 0)
            return end();
        return iterator(matrix.begin(), matrix.end(), matrix[0].begin());
    }
    iterator end() { return iterator(matrix.end(), matrix.end()); }

    class const_iterator {
     private:
        typename vector<vector<T>>::const_iterator rowiter, enditer;
        typename vector<T>::const_iterator coliter;

     public:
        const_iterator() {}

        const_iterator(typename vector<vector<T>>::const_iterator rowiterator,
                 typename vector<vector<T>>::const_iterator enditerator,
                 typename vector<T>::const_iterator coliterator)
                : rowiter(rowiterator)
                , enditer(enditerator)
                , coliter(coliterator) {}

        const_iterator(typename vector<vector<T>>::const_iterator rowiterator,
                 typename vector<vector<T>>::const_iterator enditerator)
                : rowiter(rowiterator)
                , enditer(enditerator) {}

        bool operator==(const const_iterator& other) const {
            return (rowiter == other.rowiter) && (rowiter == enditer || coliter == other.coliter);
        }
        bool operator!=(const const_iterator& other) const { return !operator==(other); }

        const T& operator*() { return *coliter; }
        const_iterator& operator++() {
            if (rowiter == enditer) return *this;
            ++coliter;
            if (coliter == (*rowiter).end() && ++rowiter != enditer)
                coliter = (*rowiter).begin();
            return *this;
        }
    };

    const_iterator begin() const {
        if (matrix.size() == 0)
            return end();
        return const_iterator(matrix.begin(), matrix.end(), matrix[0].begin());
    }
    const_iterator end() const { return const_iterator(matrix.end(), matrix.end()); }
};

Matrix MakeId(int n) {
	return Matrix(n, n, [](size_t i, size_t j) { return (i == j); });
}

Matrix pow(Matrix matrix, int k) {
	Matrix result = matrix;
	for (--k; k > 0; k >>= 1) {
		if (k % 2)
			result *= matrix;
		matrix *= matrix;
	}
	return result;
}

template<typename T>
vector<T> SolveGauss(Matrix<T> A, const vector<T>& b) {
    for (size_t i = 0; i < A.size(); ++i) {
        A[i].push_back(b[i]);
    }

    for (size_t j = 0; j < A[0].size() - 1; ++j) {
        for (size_t i = j; i < A.size(); ++i) {
            if (A[i][j]) {
                if (i != j) {
                    swap(A[i], A[j]);
                    i = j;
                }
                ld lambda = A[i][j];
                for (size_t l = j; l < A[i].size(); ++l) {
                    A[i][l] /= lambda;
                }
                for (size_t k = 0; k < A.size(); ++k) {
                    if (i != k && A[k][j]) {
                        lambda = A[k][j];
                        for (size_t l = j; l < A[k].size(); ++l) {
                            A[k][l] -= A[i][l] * lambda;
                        }
                    }
                }
                break;
            }
        }
    }

    vector<T> result(b.size());
    for (size_t i = 0; i < A.size(); ++i)
        result[i] = A[i].back();
    return result;
}

int n, m;
inline size_t enc(int i, int j) { return i * m + j; }

bool HasWay(const vector<string>& map) {
    vector<vector<char>> vis(n, vector<char>(m, 0));
    queue<pair<int, int>> bfs;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (map[i][j] == 'M') bfs.push({ i, j });
        }
    }

    while (!bfs.empty()) {
        pair<int, int> cur = bfs.front(); bfs.pop();
        int i = cur.first, j = cur.second;
        vis[i][j] = 1;
        for (int dr = i - 1; dr <= i + 1; ++dr) {
            for (int dc = j - 1; dc <= j + 1; ++dc) {
                if (dr >= 0 && dr < n && dc >= 0 && dc < m && map[dr][dc] != '#') {
                    if (!vis[dr][dc]) {
                        vis[dr][dc] = 1;
                        if (map[dr][dc] == 'C') return 1;
                        bfs.push({ dr, dc });
                    }
                }
            }
        }
    }
    return 0;
}
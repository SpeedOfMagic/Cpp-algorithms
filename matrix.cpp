template<typename T>
class Matrix {
 private:
    vector<vector<T>> matrix;
 
 public:
    const vector<T>& operator[](int i) const { return matrix[i]; }
    vector<T>& operator[](int i) { return matrix[i]; }
 
    Matrix(const vector<vector<T>>& mat) : matrix(mat) {}
 
    Matrix(size_t n) {
        matrix.resize(n, vector<T>(n));
    }
 
    Matrix(size_t n, size_t m) {
        matrix.resize(n, vector<T>(m));
    }
 
    friend std::ostream& operator<<(std::ostream& out, const Matrix<T>& m) {
        // auto [rowSize, colSize] = m.size();
        size_t rowSize = m.size().first, colSize = m.size().second;
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
        // auto [rowSize, colSize] = size();
        size_t rowSize = size().first, colSize = size().second;
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
        // auto [rowSize, colSize] = size();
        size_t rowSize = size().first, colSize = size().second;
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
        // auto [rowSize, colSize] = size();
        size_t rowSize = size().first, colSize = size().second;
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
        // auto [rowSize, colSize] = size();
        // auto [oRowSize, oColSize] = other.size();
        size_t rowSize = size().first, colSize = size().second;
        size_t oRowSize = other.size().first, oColSize = other.size().second;
        assert(colSize == oRowSize);
        Matrix res(vector<vector<T>>(rowSize, vector<T>(oColSize, T())));
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
 
template<typename T>
Matrix<T> pow(Matrix<T> matrix, int k) {
	Matrix<T> result = matrix;
	for (--k; k > 0; k >>= 1) {
        cerr << k << " ";
		if (k % 2)
			result *= matrix;
		matrix *= matrix;
	}
	return result;
}
 
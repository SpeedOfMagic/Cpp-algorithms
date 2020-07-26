class Matrix : public vector<vector<Number>> {
public:
	Matrix(size_t rows, size_t columns) {
		resize(rows);
		for (size_t i = 0; i < rows; ++i)
			operator[](i).resize(columns, 0);
	}

	template<class BinaryFunction>
	Matrix(size_t n, size_t m, BinaryFunction f) {
		*this = Matrix(n, m);
		for (size_t i = 0; i < n; ++i)
			for (size_t j = 0; j < m; ++j)
				operator[](i)[j] = f(i, j);
	}

	Matrix(const std::initializer_list<std::initializer_list<Number>>& list) {
		for (auto row : list)
			push_back(row);
	}

	size_t rows() const noexcept { return size(); }
	size_t columns() const { return operator[](0).size(); }

	Matrix T() {  // returns transpose matrix
		Matrix other(columns(), rows());
		for (size_t i = 0; i < rows(); ++i)
			for (size_t j = 0; j < columns(); ++j)
				other[j][i] = operator[](i)[j];
		return other;
	}

	Matrix operator*(const Matrix& other) const {
		assert(columns() == other.rows());
		Matrix res(rows(), other.columns());
		for (size_t i = 0; i < rows(); ++i)
			for (size_t j = 0; j < other.columns(); ++j)
				for (size_t k = 0; k < columns(); ++k)
					res[i][j] += operator[](i)[k] * other[k][j];
		return res;
	}

	Matrix operator*=(const Matrix& other) { return *this = operator*(other); }

	friend ostream& operator<<(ostream& os, const Matrix& matrix) {
		for (size_t i = 0; i < matrix.rows(); ++i) {
			for (size_t j = 0; j < matrix.columns(); ++j)
				os << matrix[i][j] << " ";
			os << endl;
		}
		return os;
	}
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

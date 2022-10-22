const long double PI = acosl(-1.0);

template<typename T = long double>
class Complex {
private:
	T real_, imag_;


public:
	Complex() = default;

	Complex(T real, T imag = 0) : real_(real), imag_(imag) {}

	Complex operator+(const Complex& other) const {
		return { real() + other.real(), imag() + other.imag() };
	}

	Complex operator*(const Complex& other) const {
		return { real() * other.real() - imag() * other.imag(),
				 real() * other.imag() + imag() * other.real() };
	}

	Complex& operator*=(const Complex& other) {
		*this = (*this) * other;
		return *this;
	}

	T real() const { return real_; }
	T imag() const { return imag_; }
};

template<typename T = long double>
class FourierTransform {
private:
	const T PI = acosl(-1.0l);

	vector<Complex<T>> roots_;

public:
	FourierTransform(size_t n) {
		assert((n & (n - 1)) == 0);
		roots_.reserve(n);
		for (size_t i = 0; i < n; ++i) {
            roots_.emplace_back(cosl(2.0l * PI * i / n), sinl(2.0l * PI * i / n));
        }
	}

	template<typename U = int>
	vector<Complex<T>> FFT(const vector<U>& poly, size_t root_index = 1) {
		if (poly.size() == 1) {
			return { static_cast<Complex<T>>(poly[0]) };
        }

		vector<U> vecs[2];  // even, odd
		for (size_t i = 0; i < poly.size(); ++i) {
			vecs[i & 1].push_back(poly[i]);
        }

		vector<Complex<T>> result_even = FFT(vecs[0], root_index << 1);
		vector<Complex<T>> result_odd = FFT(vecs[1], root_index << 1);
		vector<Complex<T>> result(poly.size());

		size_t current_index = 0;

		size_t m = result.size() / 2;
		for (size_t i = 0; i < m; ++i) {
			result[i] = result_even[i] + result_odd[i] * roots_[current_index];
			current_index += root_index;
		}
		for (size_t i = m; i < result.size(); ++i) {
			size_t d = i - m;
			result[i] = result_even[d] + result_odd[d] * roots_[current_index];
			current_index += root_index;
		}
		return result;
	}

    template<typename U = int>
	vector<U> InverseFFT(const vector<Complex<T>>& transformed) {
		assert(transformed.size() == roots_.size());

		vector<Complex<T>> fft = FFT(transformed);
		reverse(fft.begin() + 1, fft.end());

		vector<U> result(fft.size());
		for (size_t i = 0; i < fft.size(); ++i) {
			//assert(fft[i].imag() < 1e-5);
			result[i] = roundl(fft[i].real() / fft.size());
		}
		return result;
	}
};

template<typename T>
void FitForMultiply(vector<T>& vector) {
	while (vector.size() & (vector.size() - 1)) {
		vector.push_back(0);
    }
	vector.resize(vector.size() * 2, 0);
}

template<typename T = int>
vector<T> Multiply(vector<T> A, vector<T> B) {
	FitForMultiply(A);
	FitForMultiply(B);
	FourierTransform<> F(A.size());
	vector<Complex<>> Af = F.FFT(A), Bf = F.FFT(B);
	for (size_t i = 0; i < Bf.size(); ++i) {
		Af[i] *= Bf[i];
    }

	return F.InverseFFT<T>(Af);
}

string Multiply(string a, string b) {
	int m = 0;
	if (a[0] == '-') {
		a.erase(a.begin());
		++m;
	}
	if (b[0] == '-') {
		b.erase(b.begin());
		++m;
	}

	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	while (a.size() < b.size())
		a.push_back('0');
	while (b.size() < a.size())
		b.push_back('0');

	vector<int> A(a.size()), B(b.size());
	for (size_t i = 0; i < a.size(); ++i) {
		A[i] = a[i] - '0';
    }
	for (size_t i = 0; i < b.size(); ++i) {
		B[i] = b[i] - '0';
    }

	vector<int> P = Multiply(A, B);
	int carry = 0;
	for (size_t i = 0; i < P.size(); ++i) {
		P[i] += carry;
		carry = P[i] / 10;
		P[i] %= 10;
	}

	P.push_back(carry);
	while (P.size() > 1 && P.back() == 0)
		P.pop_back();

    string ans = "";
	if (m % 2 && P[0] != 0) {
		ans += "-";
    }

	for (size_t i = 0; i < P.size(); ++i) {
		ans += char('0' + P[P.size() - i - 1]);
	}
    return ans;
}

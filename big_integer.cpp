

struct BigInteger {
	const int b = 1000000000;
	vector<int> dig = {0};

	BigInteger() {}
	BigInteger(vector<int> a) {
		dig = a;
		if (dig.empty() || dig.back() != 0)
			dig.push_back(0);
	}
	BigInteger(int a) {
		dig.clear();
		while (a) {
			dig.push_back(a % b);
			a /= b;
		}
		dig.push_back(0);
	}

	void operator=(BigInteger a)  { dig = a.dig; }

	BigInteger operator+(const BigInteger& other) const {
		vector<int> ans = dig;
		bool carry = false;
		for (size_t i = 0; i < other.dig.size(); i++) {
			if (i == ans.size()) {
                ans.push_back(0);
            }
			if (carry) {
                ++ans[i];
            }

			carry = ans[i] + other.dig[i] >= b;
			ans[i] = (ans[i] + other.dig[i]) % b;
		}
		if (carry)
			ans.push_back(1);
		return BigInteger(ans);
	}

	BigInteger operator*(const BigInteger& a) const {
		vector<int> ans = vector<int>(a.dig.size() + dig.size(), 0);
		for (size_t i = 0; i < dig.size(); i++)
			for (size_t j = 0; j < a.dig.size(); j++)
				ans[i + j] += dig[i] * a.dig[j];

		int carry = 0;
		for (size_t i = 0; i < ans.size(); i++) {
			ans[i] += carry;
			carry = ans[i] / b;
			ans[i] %= b;
		}
		assert(carry == 0);
		while (ans.size() >= 2 && ans.back() == 0 && ans[ans.size() - 2] == 0)
			ans.pop_back();
		return ans;
	}

	bool operator<(const BigInteger& a) const {
		if (a.dig.size() < dig.size())
			return 0;
		else if (dig.size() < a.dig.size())
			return 1;
		for (int i = dig.size() - 1; i >= 0; i--)
			if (dig[i] > a.dig[i])
				return 0;
			else if (dig[i] < a.dig[i])
				return 1;
		return 0;
	}

    friend ostream& operator<<(ostream& o, const BigInteger& num) {
        bool leading_zeroes = true;
        for (auto it = num.dig.rbegin(); it != num.dig.rend(); ++it) {
            if ((*it) != 0) {
                leading_zeroes = false;
            }
            if (leading_zeroes && (*it) == 0) {
                continue;
            }
            o << (*it);
        }
        return o;
    }
};

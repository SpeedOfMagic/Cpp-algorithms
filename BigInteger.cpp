struct bigint {
	const int b = 1000000000;
	vector<int> dig = {0};

	bigint() {}
	bigint(vector<int> a) {
		dig = a;
		if (dig.empty() || dig.back() != 0)
			dig.push_back(0);
	}
	bigint(int a) {
		dig.clear();
		while (a) {
			dig.push_back(a % b);
			a /= b;
		}
		dig.push_back(0);
	}

	void operator=(bigint a) { dig = a.dig; }

	bigint operator+(bigint a) const {
		vector<int> ans = dig;
		bool carry = 0;
		for (int i = 0; i < a.dig.size(); i++) {
			if (ans.size() < i)
				ans.push_back(0);
			if (carry)
				ans.back()++;

			carry = ans.back() + a.dig[i] >= b;
			ans.back() = (ans.back() + a.dig[i]) % b;
		}
		if (carry)
			ans.push_back(1);
		return bigint(ans);
	}

	bigint operator*(bigint a) const {
		vector<int> ans = vector<int>(a.dig.size() + dig.size(), 0);
		for (int i = 0; i < dig.size(); i++)
			for (int j = 0; j < a.dig.size(); j++)
				ans[i + j] += dig[i] * a.dig[j];

		int carry = 0;
		for (int i = 0; i < ans.size(); i++) {
			ans[i] += carry;
			carry = ans[i] / b;
			ans[i] %= b;
		}
		assert(carry == 0);
		while (ans.size() >= 2 && ans.back() == 0 && ans[ans.size() - 2] == 0)
			ans.pop_back();
		return ans;
	}

	bool operator<(bigint a) const {
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
};
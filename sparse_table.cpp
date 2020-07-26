class SparseTable {
private:
	vector<int> msb_;  // 1 << msb[i] = most significant bit of i
	vector<vector<int>> arr_;

public:
	SparseTable(int n) {
		msb_ = vector<int>(n + 1);
		msb_[0] = -1;
		for (int i = 1; i <= n; i++)
			msb_[i] = ((i & (i - 1)) == 0) + msb_[i - 1];
		arr_ = vector<vector<int>>(n, vector<int>(msb_[n] + 1, 0));
	}

	SparseTable(const vector<int>& arr) {
		*this = SparseTable(arr.size());
		for (int i = 0; i < arr_.size(); i++)
			Append(i, arr[i]);
	}

	inline int op(int a, int b) const noexcept { return min(a, b); }

	int Query(size_t l, size_t r) const { //0-indexed, works properly if only append was called
		return op(arr_[r][msb_[r - l + 1]],
				  arr_[(1 << msb_[r - l + 1]) + l - 1][msb_[r - l + 1]]);
	}

	void Append(int pos, int element) {
		//arr[pos] = element; query(l, r) works properly if there were append(pos + 1, a), ..., append(r, z)
		arr_[pos][0] = element;
		for (int i = 1; i <= msb_[pos + 1]; i++) {
			int previous = pos - (1 << (i - 1));
			arr_[pos][i] = op(arr_[pos][i - 1], arr_[previous][i - 1]);
		}
	}
};

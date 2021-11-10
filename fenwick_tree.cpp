class FenwickTree {
private:
    vector<int64_t> tree_;

public:
    FenwickTree() = default;
    explicit FenwickTree(int n) : tree_(vector<int64_t>(n, 0)) {}
    explicit FenwickTree(const vector<int>& arr) {
        tree_.resize(arr.size(), 0);
        for (size_t i = 0; i < arr.size(); ++i) {
            add(i, arr[i]);
        }
    }

    [[nodiscard]] inline int64_t query(int r) const noexcept {
        int64_t res = 0;
        for (; r >= 0; r = (r & (r+1)) - 1)
            res += tree_[r];
        return res;
    }

    [[nodiscard]] inline int64_t query(int l, int r) const noexcept {
        return l == 0 ? query(r) : query(r) - query(l - 1);
    }

    [[nodiscard]] inline size_t size() const noexcept {
        return tree_.size();
    }

    inline void add(size_t pos, int64_t change) {
        for (; pos < tree_.size(); pos = pos | (pos + 1)) {
            tree_[pos] += change;
        }
    }
};

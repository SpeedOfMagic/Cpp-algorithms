class FenwickTree {
private:
    vector<int> tree_;

    static inline size_t lsb(size_t a) noexcept { return a & -a; }

public:
    explicit FenwickTree(int n) : tree_(vector<int>(n, 0)) {}

    [[nodiscard]] inline int query(size_t r) const noexcept {
        int res = 0;
        for (; r > 0; r -= lsb(r))
            res += tree_[r];
        return res;
    }

    [[nodiscard]] inline int query(size_t l, size_t r) const noexcept {
        return query(r) - query(l - 1);
    }

    inline void update(size_t pos, int change) {
        for (; pos < tree_.size(); pos += lsb(pos))
            tree_[pos] += change;
    }
};

class FenwickTree {
private:	
    vector<int> tree_;

public:
    FenwickTree(int n) : tree_(vector<int>(n, 0)) {}

	inline int lsb(size_t a) const noexcept { return a & -a; }
    
    inline int query(size_t r) const noexcept {
        int res = 0;
        for (; r > 0; r -= lsb(r))
            res += tree_[r];
        return res;
    }

    inline void update(size_t position, int change) {
        for (; position < tree_.size(); position += lsb(pos))
            tree_[position] += change;
    }
};


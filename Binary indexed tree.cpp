inline int lsb(int a) { return a & -a; }

struct fenwick {
    vector<int> tree;

    fenwick(int n) { tree = vector<int>(n, 0); }

    inline int query(int r) {
        int res = 0;
        for (; r; r -= lsb(r))
            res += tree[r];
        return res;
    }

    inline void update(int pos, int change) {
        for (; pos < (int) tree.size(); pos += lsb(pos))
            tree[pos] += change;
    }
};
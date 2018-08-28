int lsb(int a) { return a & -a; }

struct fenwick {
    vector<int> tree;

    fenwick(int n) { tree = vint(n); }

    int query(int l, int r) {
        if (l != 1)
            return query(1, r) - query(1, l - 1);
        int res = 0;
        while (r) {
            res += tree[r];
            r -= lsb(r);
        }
        return res;
    }

    void update(int pos, int change) {
        while (pos <= sz(tree)) {
            tree[pos] += change;
            pos += lsb(pos);
        }
    }
};
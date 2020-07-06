struct fenwick {
	inline int lsb(int a) { return a & -a; }
	
    vector<int> tree;
    fenwick(int n) { tree = vector<int>(n, 0); }

    inline int query(int r) {
        int res = 0;
        for (; r; r -= lsb(r))
            res += tree[r];
        return res;
    }

    inline void update(unsigned int pos, int change) {
        for (; pos < tree.size(); pos += lsb(pos))
            tree[pos] += change;
    }
};

/* short version
const int N = 1e5 + 1;
int tree[N];
int lsb(int a) { return a & -a; }
int query(int r) { return r ? 0 : (tree[r] + query(r - lsb(r))); }
void upd(int p, int v) { if (p < N) { tree[p] += v; upd(p + lsb(p)); } }
*/

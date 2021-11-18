class LeastCommonAncestor {
private:
    using Tree = vector<vector<int>>;

    vector<vector<int>> kth_ancestor_;
    vector<int> height_;

    inline void FillHeightKthAncestor(const Tree& tree, int cur, int p) {
        height_[cur] = (p != -1) ? (height_[p] + 1) : 0;
        for (int k = 0, d = p; d != -1; k++) {
            kth_ancestor_[cur][k] = d;
            d = kth_ancestor_[d][k];
        }

        for (int next : tree[cur]) {
            if (next != p) {
                FillHeightKthAncestor(tree, next, cur);
            }
        }
    }

public:
    LeastCommonAncestor(const Tree& tree) {
        int log_size = 0;
        while ((1 << log_size) <= tree.size()) {
            ++log_size;
        }

        kth_ancestor_ .resize(tree.size(), vector<int>(log_size, -1));
        height_.resize(tree.size());

        FillHeightKthAncestor(tree, 1, -1);
    }

    inline int LCA(int v, int u) {
        if (height_[v] > height_[u])
            swap(v, u);

        for (int k = 0, d = height_[u] - height_[v]; d; k++, d >>= 1)
            if (d & 1)
                u = kth_ancestor_[u][k];

        for (int k = kth_ancestor_[0].size() - 1; u != v;)
            if (kth_ancestor_[u][k] != kth_ancestor_[v][k] || !k) {
                u = kth_ancestor_[u][k];
                v = kth_ancestor_[v][k];
            }
            else
                k--;
        return u;
    }

    int Dist(int v, int u) { return height_[v] + height_[u] - 2 * height_[LCA(v, u)]; }

    int GetKthAncestor(int v, unsigned int distance) {
        for (int k = 0; distance && k < kth_ancestor_[0].size(); ++k, distance >>= 1) {
            if (distance & 1) {
                v = kth_ancestor_[v][k];
            }
        }
        return v;
    }

    inline bool IsAncestor(int posAncestor, int v) {
        if (height_[v] < height_[posAncestor])
            return 0;
        return GetKthAncestor(v, height_[v] - height_[posAncestor]) == posAncestor;
    }
};

class DisjointSetUnion {
private:
    vector<int> ancestor_;
    vector<int> sizes_;
    size_t components_count_ = 0;

public:
    inline int Find(int a) {
        return (ancestor_[a] == a) ? a : ancestor_[a] = Find(ancestor_[a]);
    }

    void Unite(int a, int b) {
        if (IsConnected(a, b))
            return;

        a = Find(a);
        b = Find(b);
        if (sizes_[a] > sizes_[b])
            swap(a, b);

        ancestor_[a] = b;
        sizes_[b] += sizes_[a];
        --components_count_;
    }

    inline bool IsConnected(int a, int b) { return Find(a) == Find(b); }

    inline int GetComponentsCount() const { return components_count_; }

    DisjointSetUnion(int n)
    : sizes_(vector<int>(n + 1, 1))
    , components_count_(n) {
        ++n;
        ancestor_.resize(n);
        for (int i = 0; i < n; i++)
            ancestor_[i] = i;
    }
};

class DSUWithRollback {
private:
    vector<int> ancestor_;
    vector<int> sizes_;
    size_t components_count_ = 0;

    struct Query {
        int u, v;
        char changed_something;
    };
    vector<Query> queries_;

public:
    DSUWithRollback(int n)
        : sizes_(vector<int>(n + 1, 1))
        , components_count_(n) {
        ++n;
        ancestor_.resize(n);
        for (int i = 0; i < n; i++)
            ancestor_[i] = i;
    }

    inline int Find(int a) {
        return (ancestor_[a] == a) ? a : Find(ancestor_[a]);
    }

    void Unite(int a, int b) {
        a = Find(a);
        b = Find(b);

        if (a != b) {
            if (sizes_[a] > sizes_[b])
                swap(a, b);
            ancestor_[a] = b;
            sizes_[b] += sizes_[a];
            --components_count_;
        }
        queries_.push_back({ a, b, a != b });
    }

    void Revert() {
        if (queries_.empty())
            return;

        Query query = queries_.back();
        queries_.pop_back();


        if (query.changed_something) {
            sizes_[query.u] -= sizes_[query.v];
            ancestor_[query.u] = query.u;
            ++components_count_;
        }
    }

    inline bool IsConnected(int a, int b) { return Find(a) == Find(b); }

    inline int GetComponentsCount() const { return components_count_; }
};
const int D = 31;
const int N = 1 << (D - 1);

struct segTree {
    segTree *l = nullptr, *r = nullptr;
    char val = 0;
};

inline segTree* Left(segTree *t) { return (t == nullptr) ? nullptr : t -> l; }
inline segTree* Right(segTree *t) { return (t == nullptr) ? nullptr : t -> r; }
inline char val(segTree *t) { return (t == nullptr) ? 0 : t -> val; }

inline void pushdown(segTree *t) {
    if (Left(t) != nullptr)
        t -> l -> val |= t -> val;
    if (Right(t) != nullptr)
        t -> r -> val |= t -> val;
}

segTree* update(int l, int r, segTree *par, int ll = 1, int rr = N) {
    segTree *cur = new segTree();
    cur -> val = val(par) || (l == ll && r == rr);
    if (cur -> val)
        return cur;
    int mid = (ll + rr) >> 1;
    if (l <= mid) 
        cur -> l = update(l, min(r, mid), Left(par), ll, mid);
    else
        cur -> l = Left(par);
    
    if (mid < r)
        cur -> r = update(max(l, mid + 1), r, Right(par), mid + 1, rr);
    else
        cur -> r = Right(par);

    if (cur -> val == 0)
        cur -> val = val(Left(cur)) & val(Right(cur));
    return cur;
}

int query(int l, int r, segTree *cur, int ll = 1, int rr = N) {
    if (l > r)
        return 0;
    if (val(cur))
        return 1;
    if (l == ll && r == rr)
        return val(cur);
    int mid = (ll + rr) >> 1;
    return query(l, min(r, mid), Left(cur), ll, mid) |
		   query(max(l, mid + 1), r, Right(cur), mid + 1, rr);
}


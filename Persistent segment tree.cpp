struct segTree {
    int val;
    segTree *left = nullptr, *right = nullptr;
    segTree(int v):val(v) {}
};

int n;

v<segTree*> version = {nullptr};

int query(int l, int r, segTree *cur, int ll = 0, int rr = n - 1) {
    if (cur == nullptr || l > r)
        return 0;
    if (l == ll && r == rr)
        return cur -> val;
    int mid = (ll + rr) / 2;
    return query(l, min(r, mid), cur -> left, ll, mid) + query(max(l, mid + 1), r, cur -> right, mid + 1, rr);
}

int value(segTree* cur) {
    if (cur == nullptr)
        return 0;
    return cur -> val;
}

segTree* left(segTree* cur) {
    if (cur == nullptr)
        return nullptr;
    return cur -> left;
}

segTree* right(segTree* cur) {
    if (cur == nullptr)
        return nullptr;
    return cur -> right;
}

void update(int num, int val) {
    segTree* parallel = version.back();
    version.pb(new segTree(value(parallel) + val));
    segTree* cur = version.back();

    int ll = 0, rr = n - 1;
    while (ll != rr) {
        int mid = (ll + rr) / 2;
        if (num > mid) {
            ll = mid + 1;
            cur -> left = left(parallel);
            parallel = right(parallel);
            cur -> right = new segTree(value(parallel) + val);
            cur = cur -> right;
        } else {
            rr = mid;
            cur -> right = right(parallel);
            parallel = left(parallel);
            cur -> left = new segTree(value(parallel) + val);
            cur = cur -> left;
        }
    }
}
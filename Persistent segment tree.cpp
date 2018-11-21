struct segTree {
    int val = 0;
    segTree* left = nullptr;
	segTree* right = nullptr;
    segTree(int v) : val(v) {}
	segTree() {}
};

int n;
v<segTree*> version = {nullptr};

int value(segTree* cur) { return (cur == nullptr) ? 0 : cur -> val; }

segTree* left(segTree* cur) { return ((cur == nullptr) ? nullptr : cur -> left); }
segTree* right(segTree* cur) { return ((cur == nullptr) ? nullptr : cur -> right); }

int query(int l, int r, segTree* cur, int ll = 1, int rr = n) {
    if (l > r)
        return 0;
    if (l == ll && r == rr)
        return value(cur);
    int mid = (ll + rr) / 2;
    return query(l, min(r, mid), cur -> left, ll, mid) +
		   query(max(l, mid + 1), r, cur -> right, mid + 1, rr);
}

void update(int num, int val) {
    segTree* parallel = version.back();
    version.pb(new segTree(value(parallel) + val));
    segTree* cur = version.back();
    stack<segTree*> route;

    int ll = 1, rr = n;
    while (ll != rr) {
        route.push(cur);
        int mid = (ll + rr) / 2;
        if (num > mid) {
            ll = mid + 1;
            cur -> left = left(parallel);
            parallel = right(parallel);
            cur -> right = new segTree();
            cur = cur -> right;
        } else {
            rr = mid;
            cur -> right = right(parallel);
            parallel = left(parallel);
            cur -> left = new segTree();
            cur = cur -> left;
        }
    }
	cur -> val += val;
    while (!route.empty()) {
        route.top() -> val = value(left(route.top())) + value(right(route.top()));
        route.pop();
    }
}
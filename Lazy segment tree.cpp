int f(int a, int b) { //f - query you need to calculate, but for two values
    return a + b;
}
const int nothing = 0; //nothing means that f(x, nothing)=x
struct segTreeNode {
    int val = nothing, lazy = 0;

    segTreeNode(){}

    void update(int l, int r, int s) { //function that updates single node from lazy
        val += (r - l + 1) * s;
    }
};

v<segTreeNode> segTree;
int n, tot;

void processLazy(int cur) {
    if (segTree[cur].lazy != 0) {
        segTree[cur].update(l, r, segTree[cur].lazy);
        if(cur < tot) {
            segTree[cur * 2].lazy += segTree[cur].lazy;
            segTree[cur * 2 + 1].lazy += segTree[cur].lazy;
        }
        segTree[cur].lazy = 0;
    }
}

void update(int l, int r, int s, int cur = 1, int ll = 1, int rr = tot) {
    bool finish = 0;
    if (l == ll && r == rr) {
        segTree[cur].lazy += s;
        finish = 1;
    }

	processLazy(cur);

    if (finish || l > r)
        return;

    int mid = (ll + rr) / 2;
    update(l, min(r, mid), s, cur * 2, ll, mid);
    update(max(l, mid + 1), r, s, cur * 2 + 1, mid + 1, rr);

    segTree[cur].val = f(segTree[cur * 2].val, segTree[cur * 2 + 1].val);
}

int query(int l, int r, int cur = 1, int ll = 1, int rr = tot) {
    processLazy(cur);
	
	if (l > r)
        return nothing;

    if (l == ll && r == rr)
        return segTree[cur].val;

    int mid = (ll + rr) / 2;
    return f(query(l, min(r, mid), cur * 2, ll, mid), query(max(l, mid + 1), r, cur * 2 + 1, mid + 1, rr));
}

void init(vector<int> vals) {
    n = vals.size();
    tot = n;
    while(tot & (tot - 1))
        tot++;

    segTree = vector<segTreeNode>(2 * tot);
    for (int i = tot; i < tot + n; i++)
        segTree[i].val = vals[i - tot];

    for (int i = tot - 1; i; i--)
        segTree[i].val = f(segTree[i * 2].val, segTree[i * 2 + 1].val);
}
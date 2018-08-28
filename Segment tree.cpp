//you want to set 2 functions: f(int a, int b) and segTreeNode::update(int val) and 1 parameter: nothing

const int nothing = 0; //nothing means that f(x, nothing) = x

struct segTreeNode {
    int val = nothing;

    segTreeNode(int _val) : val(_val) {}

    void update(int _val) { //function that updates node based on val
        this -> val += _val;
    }
};

vector<segTreeNode> segTree;
int n, tot;

int f(int a, int b) { //f - query you need to calculate, but for two values
    return segTree[a].val + segTree[b].val;
}

void update(int nodeToUpdate, int value, int cur = 1, int ll = 1, int rr = tot) {
    if (ll == rr) {
        segTree[cur].update(value);
        return;
    }

    int p = (ll + rr) / 2;

    if (nodeToUpdate <= p)
        update(nodeToUpdate, value, cur * 2, ll, p);
    else
        update(nodeToUpdate, value, cur * 2 + 1, p + 1, rr);

    segTree[cur] = f(cur * 2, cur * 2 + 1);
}

int query(int l, int r, int cur = 1, int ll = 1, int rr = tot) {
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
    while (tot & (tot - 1))
        tot++;

    segTree = vector<segTreeNode>(tot * 2, segTreeNode(nothing));

    for (int i = 0; i < n; i++)
        segTree[i + tot].val = vals[i];

    for (int i = tot - 1; i; i--)
        segTree[i] = f(i * 2, i * 2 + 1);
}
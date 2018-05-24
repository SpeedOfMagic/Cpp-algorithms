//you want to set 2 functions: f(int a, int b) and update(int val) and 1 parameter: nothing

int f(int a, int b) { //f - query you need to calculate, but for two values
    return a + b;
}

const int nothing = 0; //nothing means that f(x, nothing)=x

struct segTreeNode{
    int val = nothing;

    segTreeNode* left = nullptr;
    segTreeNode* right = nullptr;

    segTreeNode(int val) : val(val) {}

    void update(int val) { //function that updates node based on val
        this -> val += val;
    }

    void update() { //function that updates node based on children
        this -> val = f(this -> left -> val, this -> right -> val);
    }
};

vector<segTreeNode> segTree;
int n, tot;

void update(int nodeToUpdate, int value, int cur = 1, int ll = 1, int rr = tot) {
    if (ll == nodeToUpdate && nodeToUpdate == rr){
        segTree[cur].update(value);
        return;
    }

    int p = (ll + rr) / 2;

    if (nodeToUpdate <= p)
        update(nodeToUpdate, value, cur*2, ll, p);
    else
        update(nodeToUpdate,value,cur*2+1,p+1,rr);

    segTree[cur].update();
}

int query(int l, int r, int cur=1, int ll=1, int rr=tot) {
    if (l > r)
        return nothing;
    else if (l == ll && r == rr)
        return segTree[cur].val;

    int p = (ll + rr) / 2;

    return f(
        query(l, min(r,p), cur * 2, ll, p),
        query(max(l, p + 1), r, cur * 2 + 1, p + 1, rr)
    );
}

void init(vector<int> vals) {
    n = vals.size();

    tot = n;
    while (tot & (tot - 1))
        tot++;

    segTree = vector<segTreeNode>(2*tot, segTreeNode(nothing));

    for (int i = 0; i < n; i++)
        segTree[i + tot].val = vals[i];

    for (int i = tot - 1; i > 0; i--){
        segTree[i].left = &segTree[i*2];
        segTree[i].right = &segTree[i*2+1];

        segTree[i].update();
    }
}

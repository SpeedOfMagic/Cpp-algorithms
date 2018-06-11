const int inf = 1e9;

int getRandom(int limit) { //returns random value in half-interval [0; limit);
    //don't forget to write srand(time(0));
    return ((rand()<<16) + rand()) % limit;
}

struct waveletTree{
    waveletTree *left = nullptr, *right = nullptr;
    int l = inf, r = -inf;
    vector<int> sequence;
    vector<unsigned int> mapLeft, mapRight;

    waveletTree(int l, int r, vector<int>& sequence): l(l), r(r), sequence(sequence) {}
    waveletTree(){}
};

waveletTree* root;

void init(waveletTree* nodeToInit) {
    int mn = nodeToInit -> l, mx = nodeToInit -> r;
    
    if (mn != mx) { //this also means that current node is not a leaf
        int indexOfMiddle = getRandom(nodeToInit -> sequence.size());
        int middle = nodeToInit -> sequence[indexOfMiddle];
        if (middle == mx)
            middle--;

        nodeToInit -> left = new waveletTree();
        nodeToInit -> right = new waveletTree();

        for(int i : nodeToInit -> sequence) {
            if (i <= middle) {
                nodeToInit -> left -> sequence.push_back(i);
                nodeToInit -> left -> l = min(nodeToInit -> left -> l, i);
                nodeToInit -> left -> r = max(nodeToInit -> left -> r, i);
            } else {
                nodeToInit -> right -> sequence.push_back(i);
                nodeToInit -> right -> l = min(nodeToInit -> right -> l, i);
                nodeToInit -> right -> r = max(nodeToInit -> right -> r, i);
            }
            nodeToInit -> mapLeft.push_back(nodeToInit -> left -> sequence.size());
            nodeToInit -> mapRight.push_back(nodeToInit -> right -> sequence.size());
        }

        init(nodeToInit -> left);
        init(nodeToInit -> right);
    }

}

waveletTree* init(vector<int>& sequence, int mn = inf, int mx = -inf) {
    if (mn > mx)
        for (int i : sequence) {
            mn = min(mn, i);
            mx = max(mx, i);
        }

    waveletTree* nodeToInit = new waveletTree(mn, mx, sequence);

    init(nodeToInit);

    return nodeToInit;
}

int equalTo(int q, int l, int r, waveletTree* cur = root) {
    if (l != 1)
        return equalTo(q, 1, r) - equalTo(q, 1, l - 1);

    if (cur -> l == cur -> r) //this condition checks if current node is a leaf
        return r;

    int middle = cur -> left -> r;

    if (q <= middle)
        return equalTo(q, l, cur -> mapLeft[r - 1], cur -> left);
    else
        return equalTo(q, l, cur -> mapRight[r - 1], cur ->right);
}

int lessThan(int q, int l, int r, waveletTree* cur = root) {
    if(l != 1)
        return lessThan(q, 1, r) - lessThan(q, 1, l-1);

    if (cur -> l == cur -> r || r == 0) //this condition checks if current node is a leaf
        return 0;

    int middle = cur -> left -> r;

    if (q <= middle)
        return lessThan(q, l, cur -> mapLeft[r - 1], cur -> left);
    else
        return cur -> mapLeft[r - 1] + lessThan(q, l, cur -> mapRight[r - 1], cur ->right);
}

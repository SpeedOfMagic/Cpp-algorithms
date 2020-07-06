mt19937 rng(random_device{}());
struct waveletTree{
    waveletTree *left = nullptr, *right = nullptr;
    int l, r;
    vector<unsigned int> mapLeftVector;

    unsigned int mapLeft(int i) { return mapLeftVector[i]; }
    
    unsigned int mapRight(int i) { return i - mapLeftVector[i] + 1; }

    waveletTree(int _l, int _r): l(_l), r(_r) {}
};

waveletTree* root;

void init(waveletTree* nodeToInit, vector<int>& sequence) {
    int mn = nodeToInit -> l, mx = nodeToInit -> r;
    
    if (mn != mx) { //this also means that current node is not a leaf
        int indexOfMiddle = rng() % sequence.size();
        int middle = sequence[indexOfMiddle];
        if (middle == mx)
            middle--;

        nodeToInit -> left = new waveletTree(mx, mn);
        nodeToInit -> right = new waveletTree(mx, mn);
        
        vector<int> sequenceLeft;
        vector<int> sequenceRight;
        for(int i : sequence) {
            if (i <= middle) {
                sequenceLeft.push_back(i);
                nodeToInit -> left -> l = min(nodeToInit -> left -> l, i);
                nodeToInit -> left -> r = max(nodeToInit -> left -> r, i);
            } else {
                sequenceRight.push_back(i);
                nodeToInit -> right -> l = min(nodeToInit -> right -> l, i);
                nodeToInit -> right -> r = max(nodeToInit -> right -> r, i);
            }
            nodeToInit -> mapLeftVector.push_back(sequenceLeft.size());
        }

        init(nodeToInit -> left, sequenceLeft);
        init(nodeToInit -> right, sequenceRight);
    }

}

waveletTree* init(vector<int>& sequence) {
    if (sequence.empty())
        return nullptr;
        
    int mn = *min_element(sequence.begin(), sequence.end());
    int mx = *max_element(sequence.begin(), sequence.end());

    waveletTree* nodeToInit = new waveletTree(mn, mx);

    init(nodeToInit, sequence);

    return nodeToInit;
}

int equalTo(int q, int l, int r, waveletTree* cur = root) {
    if (l != 1)
        return equalTo(q, 1, r) - equalTo(q, 1, l - 1);

    if (cur -> l == cur -> r || r == 0) //this condition checks if current node is a leaf
        return r;

    int middle = cur -> left -> r;

    if (q <= middle)
        return equalTo(q, l, cur -> mapLeft(r - 1), cur -> left);
    else
        return equalTo(q, l, cur -> mapRight(r - 1), cur ->right);
}

int lessThan(int q, int l, int r, waveletTree* cur = root) {
    if(l != 1)
        return lessThan(q, 1, r) - lessThan(q, 1, l-1);

    if (cur -> l == cur -> r || r == 0) //this condition checks if current node is a leaf
        return 0;

    int middle = cur -> left -> r;

    if (q <= middle)
        return lessThan(q, l, cur -> mapLeft(r - 1), cur -> left);
    else
        return cur -> mapLeft(r - 1)+ lessThan(q, l, cur -> mapRight(r - 1), cur -> right);
}


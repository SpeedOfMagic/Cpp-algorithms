struct waveletTree{
    waveletTree *left = nullptr, *right = nullptr;
    int l, r;
    vector<int> sequence;

    waveletTree(int l, int r, vector<int>& sequence): l(l), r(r), sequence(sequence) {}
};

waveletTree* root;

waveletTree* init(vector<int>& sequence, int mn = inf, int mx = -inf) {
    if (mx < mn){
        for(int i : sequence){
            mn = min(mn, i);
            mx = max(mx, i);
        }
    }

    waveletTree* nodeToInit = new waveletTree(mn, mx, sequence);

    if(mn != mx) {
        int middle = (mn + mx) / 2;
        vector<int> sequence1, sequence2;

        for(int i : sequence)
            if (i <= middle)
                sequence1.push_back(i);
            else
                sequence2.push_back(i);

        nodeToInit -> left = init(sequence1, mn, middle);
        nodeToInit -> right = init(sequence2, middle + 1, mx);
    }

    return nodeToInit;
}

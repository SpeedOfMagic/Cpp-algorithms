const long long inf=4611686018427387903; //2^62-1

int random() {
    srand(time(0));
    return (rand() << 16) + rand();
}

struct treap{
    treap* left = nullptr;
    treap* right = nullptr;
    int w, val, size = 1;
    int minInTree;
    treap(int val):
        w(random()),
        val(val),
        minInTree(val)
    {}
};

int size(treap* a) {
    if(a == nullptr)
        return 0;
    else
        return a -> size;
}

int minInTree(treap* a) {
    if(a == nullptr)
        return inf;
    else
        return a -> minInTree;
}

void update(treap* a){
    a -> size = size(a -> left) + size(a -> right) + 1;
    a -> minInTree = min(minInTree(a -> left), min(a -> val, minInTree(a -> right)));
}

treap* merge(treap* v1, treap* v2){
    if(v1 == nullptr)
        return v2;
    if(v2 == nullptr)
        return v1;
    
    if(v1 -> w > v2->w){
        v1 -> right = merge(v1 -> right, v2);
        update(v1);
        return v1;
    } else {
        v2 -> left = merge(v1, v2 -> left);
        update(v2);
        return v2;
    }
}

pair<treap*,treap*> split(treap* w, int k){
    if(w == nullptr)
        return {nullptr,nullptr};
    
    if(size(w -> left) >= k) {
        auto tmp = split(w -> left, k);
        w -> left = tmp.second;
        update(w);
        return {tmp.first, w};
    } else {
        auto tmp = split(w -> right, k - size(w -> left) - 1);
        w -> right = tmp.first;
        update(w);
        return {w, tmp.second};
    }
}

void prnt(treap* a) {
    if(a == nullptr)
        return;
    
    prnt(a -> left);
    cout << (a -> val) << " ";
    prnt(a -> right);
}

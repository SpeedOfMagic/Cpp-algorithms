const int N = 1e6 + 1;
int repr[N];
int siz[N];

int find(int a) {
    if (repr[a] == a)
        return a;
    else
        return repr[a] = find(repr[a]);
}

void unite(int a,int b) {
    a = find(a);
    b = find(b);
    
    if (siz[a] > siz[b])
        swap(a,b);
    
    repr[a] = b;
    
    siz[b] += siz[a];
}

bool connected(int a,int b) {
    return find(a) == find(b);
}

void init() {
    for(int i = 0; i < N; i++){
        repr[i] = i;
        siz[i] = 1;
    }
}

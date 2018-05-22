const int N = 1e6 + 1;
int a[N];
int b[N]; //extra array

void mergesort(int l, int r) {
    if (r - l + 1 < 2)
        return;
    
    int cur = (l + r) / 2;
    
    mergesort(l, cur);
    mergesort(cur + 1, r);
    
    merge(a + l, a + cur + 1, a + cur + 1, a + r + 1, b);
    
    for (int i = l; i <= r; i++)
        a[i] = b[i-l];
}

void quicksort(int l, int r) {
    srand(time(0));
    
    int ind = ((rand() << 16) + rand()) % (r - l) + l;
    int val = a[ind];
    int ll = l;
    int rr = r;
    
    while (1) {
        while (a[ll] < val)
            ll++;
        
        while (a[rr] > val)
            rr--;
        
        if (ll>rr)
            break;
        
        swap(a[ll], a[rr]);
        
        ll++;
        rr--;
    }
    if (l < rr)
        quicksort(l,rr);
    if (ll < r)
        quicksort(ll,r);
}

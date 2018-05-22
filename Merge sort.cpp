const int N = 1e6 + 1;
int a[N];
int b[N];

void mergesort(int l, int r) {
    if (r - l + 1 < 2)
        return;
    
    int cur = (l + r) / 2;
    
    mergesort(l, cur);
    mergesort(cur + 1, r);
    
    merge(a + l, a + cur + 1, a + cur + 1, a + r + 1, b);
    
    for(int i = l;i <= r; i++)
        a[i] = b[i-l];
}

vector<int> a;
int calculateInversions(int l = 0, int r = a.size() - 1) {
    if (l == r)
        return;
    else if (l + 1 == r) {
        if (a[l] > a[r]) {
            ans++;
            swap(a[l], a[r]);
        }
        return;
    }

    int middle = (l + r) / 2;
    
    int res = 0;

    res += calculateInversions(l, middle);
    res += calculateInversions(middle + 1, r);

    int p1 = l, p2 = middle + 1;
    int left = 0;
    vint b;
    while (p1 <= middle || p2 <= r) {
        if (p2 <= r && (p1 > middle || a[p1] > a[p2])) {
            b.pb(a[p2++]);
            left++;
        } else {
            b.pb(a[p1++]);
            res += left;
        }
    }
    rep(i, l, r + 1)
        a[i] = b[i - l];
    
    return left;
}

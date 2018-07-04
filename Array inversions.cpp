vector<int> a;
int calculateInversions(int l, int r) {
    if (l == r)
        return 0;
    else if (l + 1 == r) {
        if (a[l] > a[r]) {
            swap(a[l], a[r]);
            return 1;
        }
        return 0;
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

    return res;
}

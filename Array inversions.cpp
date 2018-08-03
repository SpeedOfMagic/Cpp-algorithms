vector<int> a;
long long calculateInversions(int l, int r) {
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

    long long res = 0;

    res += calculateInversions(l, middle);
    res += calculateInversions(middle + 1, r);

    int p1 = l, p2 = middle + 1;
    int left = 0;
    vector<int> b;
    while (p1 <= middle || p2 <= r) {
        if (p2 <= r && (p1 > middle || a[p1] > a[p2])) {
            b.push_back(a[p2++]);
            left++;
        } else {
            b.push_back(a[p1++]);
            res += left;
        }
    }
    rep(i, l, r + 1)
        a[i] = b[i - l];

    return res;
}

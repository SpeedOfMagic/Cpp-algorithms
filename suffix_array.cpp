struct elem {
    int c1, c2, id;
    bool operator<(const elem& o) const { return tie(c1, c2) < tie(o.c1, o.c2); }
};

std::vector<int> make_sufarray(string s) {
    s += "$";
    int n = static_cast<int>(s.size());
    std::vector<int> p(n);
    int c[n];
    for (int i = 0; i < n; ++i)
        p[i] = i;
    sort(p.begin(), p.end(), [&s](int a, int b) { return s[a] < s[b]; });
    for (int i = 0; i < n; ++i)
        c[p[i]] = (i ? c[p[i - 1]] + (s[p[i - 1]] < s[p[i]]) : 0);
    int logN = 0;
    while ((1 << logN) <= n)
        ++logN;
    for (int i = 1; i <= logN; ++i) {
        elem elems[n];
        for (int j = 0; j < n; ++j)
            elems[j] = {c[p[j]], c[(p[j] + (1 << (i - 1))) % n], p[j]};
        sort(elems, elems + n);
        for (int j = 0; j < n; ++j) {
            p[j] = elems[j].id;
            c[p[j]] = j ? (c[p[j - 1]] + (elems[j - 1] < elems[j])) : 0;
        }
    }
    return pw;
}

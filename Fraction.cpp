struct frac {
    int p, q;
    frac() {}
    frac(int _p, int _q) : p(_p), q(_q) {}
    double val() { return double(p) / double(q); }
    bool operator< (frac other) { return p * other.q < other.p * q; }
    frac reduce() { int g = __gcd(p, q); return frac(p / g, q / g); }
    frac operator+ (frac other) { return frac(p * other.q + other.p * q, q * other.q).reduce(); }
    frac operator- () { return frac(-p, q); }
    frac operator- (frac other) { return (*this) + -other; }
    frac operator* (frac other) { return frac(p * other.p, q * other.q).reduce(); }
    bool operator== (frac other) { return p == other.p && q == other.q; }
};
ostream& operator<< (ostream& o, frac f) { return o << f.p << "/" << f.q; }
bool isPowerOfTwo(int a) { return ! (a & (a - 1)); }

bool hasAdjancent1(int a) { return a & (a >> 1); }

int lsb(int a){ return a & (-a); }

int msb(int i) {
    i |= (i >>  1);
    i |= (i >>  2);
    i |= (i >>  4);
    i |= (i >>  8);
    i |= (i >> 16);
    return i - ((unsigned)i >> 1);
}

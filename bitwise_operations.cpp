bool IsPowerOfTwo(int a) { return ! (a & (a - 1)); }

bool HasAdjancent1(int a) { return a & (a >> 1); }

int lsb(int a){ return a & (-a); }  // Returns the least significant bit

int msb(int i) {  // Returns the most significant bit
    i |= (i >>  1);
    i |= (i >>  2);
    i |= (i >>  4);
    i |= (i >>  8);
    i |= (i >> 16);
    return i - ((unsigned)i >> 1);
}

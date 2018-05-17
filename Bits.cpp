bool isPowerOfTwo(int a){
    return !(a&(a-1));
}
int lsb(int a){
    return a&(-a);
}

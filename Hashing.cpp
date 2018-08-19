const long long mod2 = 36028797018963913; //2^55 - 55
const long long base = 29;
const char startingLetter = 'a'; //starting letter of the alphabet

long long hashChar(char c){
    return c - startingLetter + 1;   
}

long long hashStr(long long prevHash, char curChar, long long mod = mod2) {
    return ((prevHash * base) % mod + hashChar(curChar)) % mod;
}

long long hashStr(string& s) {
    long long res = 0;
    
    for(char i : s)
        res = hashStr(res, i);
    
    return res;
}
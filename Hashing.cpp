сonst long long mod1 = 35184372088777; //2^45 - 55
const long long mod2 = 36028797018963913; //2^55 - 55
const long long base = 29;
const char startingLetter = 'a'; //starting letter of the alphabet

long long hashChar(char c){
    return c - startingLetter + 1;   
}

long long hashStr(long long prevHash, char curChar, long long mod) {
    return ((prevHash * base) % mod + hashChar(curChar)) % mod;
}

pair<long long, long long> hashStr(string& s) {
    long long res1 = 0;
    long long res2 = 0;
    
    for(char i : s) {
        res1 = hashStr(res1, i);
        res2 = hashStr(res2, i);
    }
    
    return {res1, res2};
}


const long long mod2 = 36028797018963913; //2^55-55
const long long base = 26; //alphabet size
const char startingLetter = 'a'; //starting letter of the alphabet
long long hashChar(char c){
    return c - startingLetter + 1;   
}
long long hashStr(long long prevHash, char curChar){
    return ((prevHash * 26) % mod2 + hashChar(curChar)) % mod2;
}
long long hashStr(string& s){
    long long res = 0;
    for(char i : s)
        res = hashStr(res, i);
    return res;
}


const long long mod2 = 36028797018963913; //2^55-55
long long hashStr(string& s){
    long long base = 26;
    long long res = 0;
    for(int i = 0; i < (int) s.length(); i++)
        res=((res * base) % mod2 + (s[i] - 'a' + 1)) % mod2;
    return (res + mod2) % mod2;
}
int hashStr(int prevHash, char curChar){
    return ((prevHash * 26) % mod2 + (curChar - 'a' + 1)) % mod2;
}

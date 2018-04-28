const int mod2=36028797018963913; //2^55-55
int hashStr(str& s){
    int base=26;
    int res=0;
    for(int i=0;i<sz(s);i++)res=((res*base)%mod2+s[i]-'a'+1)%mod2;
    return (res+mod2)%mod2;
}
int hashStr(int prevHash,char curChar){return ((prevHash*26)%mod2+curChar-'a'+1)%mod2;}

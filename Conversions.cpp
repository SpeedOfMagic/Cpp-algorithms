string inttostr(int a){
    if(a==0)return "0";
    string res="";
    for(;a;a/=10)res+=a%10+'0';
    reverse(res.begin(),res.end());
    return res;
}
int strtoint(string a){
    int res=0;
    for(char i:a)res=res*10+(i-'0');
    return res;
}
double strtod(string a){
    double res=0;
    double afterDot=1;
    bool dotBegins=0;
    for(char i:a){
        if(dotBegins)afterDot*=10;
        if(i=='.')dotBegins=1;
        else res=(res*10)+(i-'0');
    }
    return res/afterDot;
}

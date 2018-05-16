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

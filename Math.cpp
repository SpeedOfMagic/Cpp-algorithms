int gcd(int a,int b){
    a=abs(a); b=abs(b);
    if (a==0 && b==0) return 0;
    if (a>b)swap(a,b);
    if (a)return gcd(a,b%a);
    return b;
}
int lcm(int a,int b){return a/gcd(a,b)*b;}
int fact(int a,int mod){if (a==1)return 1;else return (a*fact(a-1,mod))%mod;}
int sign(int a){return max(min((int)1,a),(int)-1);}
bool prime(int a){
    if(a<2)return 0;if(a==2)return 1;
    for(int b=2;b<=ceil(sqrt(a));b++)if(a%b==0)return 0;
    return 1;
}
int pow(int a,int b,int mod){
    if(b==0)return 1;
    if(b==1)return a;
    int res=pow(a,b/2,mod);
    res=(res*res)%mod;
    if(b%2)return (a*res)%mod;
    return res;
}

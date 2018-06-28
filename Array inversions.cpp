/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
#define int long long
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define sz(a) ((int) a.size())
const int inf = 4611686018427387903; //2^62 - 1
#if 0  //FileIO
const string fileName = "graphgame";
ifstream fin ((fileName == "" ? "input.txt"  : fileName + ".in" ));
ofstream fout((fileName == "" ? "output.txt" : fileName + ".out"));
#define get fin>>
#define put fout<<
#else
#define get cin>>
#define put cout<<
#endif
#define eol put endl
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here
vint a;
int ans = 0;
void calculateInversions(int l, int r) {
    if (l == r)
        return;
    else if (l + 1 == r) {
        if (a[l] > a[r]) {
            ans++;
            swap(a[l], a[r]);
        }
        return;
    }

    int middle = (l + r) / 2;

    calculateInversions(l, middle);
    calculateInversions(middle + 1, r);

    int p1 = l, p2 = middle + 1;
    int left = 0;
    //for(int i:a)print(i);eol;
    vint b;
    while (p1 <= middle || p2 <= r) {
        //debug(l, r, p1, p2, a[p1], a[p2], ans, left);
        if (p2 <= r && (p1 > middle || a[p1] > a[p2])) {
            b.pb(a[p2++]);
            left++;
        } else {
            b.pb(a[p1++]);
            ans += left;
        }
    }
    rep(i, l, r + 1)
        a[i] = b[i - l];
}
void run() {
    int n;
    get n;
    n++;
    a = vint(n);
    rep(i, 1, n)
        get a[i];

    mergesort(1, n - 1);
    put ans;
}
int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}

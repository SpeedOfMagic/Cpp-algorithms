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
const long long inf = 4611686018427387903; //2^62 - 1
#if 0  //FileIO
const string fileName = "";
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
const int N = 1e5 + 1;

vector<int> g[N]; //init me
int height[N];

const int M = 20;
int kthAncestor[N][M];

void precalc(int cur, int h = 0, int p = -1) {
    height[cur] = h;

    for (int j = 0; j < M; j++)
        kthAncestor[cur][j] = -1;
    if (p != -1) {
        kthAncestor[cur][0] = p;
        int pos = p;
        int k = 0;
        while (kthAncestor[pos][k] != -1) {
            kthAncestor[cur][k + 1] = kthAncestor[pos][k];
            pos = kthAncestor[pos][k];
            k++;
        }
    }

    for (int i : g[cur])
        if (i != p)
            precalc(i, h + 1, cur);
}

int getKthAncestor(int v, unsigned int distance) {
    int k = 0;
    while (distance && k < M) {
        if (distance & 1)
            v = kthAncestor[v][k];
        distance >>= 1;
        k++;
    }

    return v;
}

int lca(int v, int u) {
    if (height[v] > height[u])
        swap(v, u);

    int d = height[u] - height[v];

    u = getKthAncestor(u, d);

    int k = M - 1;

    while (v != u)
        if (kthAncestor[v][k] != kthAncestor[u][k] || k == 0) {
            v = kthAncestor[v][k];
            u = kthAncestor[u][k];
        } else
            k--;

    return v;
}

int distance(int v, int u, int theirLCA = -1) {
    if (theirLCA == -1)
        theirLCA = lca(v, u);

    return height[v] + height[u] - 2 * height[theirLCA];
}

void run() {
    int n;
    get n;
    n++;
    rep(i, 2, n) {
        int v, u;
        read(v, u);
        g[v].pb(u);
        g[u].pb(v);
    }

    precalc(1);

}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}

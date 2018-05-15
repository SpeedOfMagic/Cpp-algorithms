#include <bits/stdc++.h>
using namespace std;
#define rep(a,l,r) for(int a=(l);a<(r);a++)
#define get cin>>
void read(){}  template<typename Arg,typename... Args> void read(Arg& arg,Args&... args){get (arg);read(args...);}
//code goes here
const int N=200001;
stack<int>l;
bool vis[N];
int ans[N];
set<int>g[N],rev[N];
int col=1;
void korasaju(int cur,bool todo){
    if (todo){
        ans[cur]=col;
        for(int i:rev[cur])if(ans[i]==0)korasaju(i,todo);
    } else {
        vis[cur]=1;
        for(int i:g[cur])if(!vis[i])korasaju(i,todo);
        l.push(cur);
    }
}
void run(){
    int n,m;read(n,m);
    n++;
    for(int i=0;i<m;i++){
        int u,w;read(u,w);
        g[u].insert(w);
        rev[w].insert(u);
    }
    rep(i,1,n)vis[i]=0;
    rep(i,1,n)if(!vis[i])korasaju(i,0);
    while(!l.empty()){
        if(ans[l.top()]==0){korasaju(l.top(),1);col++;}
        l.pop();
    }
}
int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);run();return 0;}

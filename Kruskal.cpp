int repr[(int)3e5],siz[(int)3e5];
int find(int a){
    if(repr[a]==a)return a;
    else return repr[a]=find(repr[a]);
}
void unite(int a,int b){
    if(siz[a]>siz[b])swap(a,b);
    a=find(a);
    b=find(b);
    repr[a]=b;
    siz[b]+=siz[a];
}
bool connected(int a,int b){return find(a)==find(b);}
void run(){
    int n,m;read(n,m);n++;
    rep(i,1,n){repr[i]=i;siz[i]=1;}
    vint edges[m];rep(i,0,m){edges[i]=vint(3);read(edges[i][1],edges[i][2],edges[i][0]);}
    sort(edges,edges+m);
    int ans=0;
    for(int i=0;i<m;i++){
        if(!connected(edges[i][1],edges[i][2])){
            ans+=edges[i][0];
            unite(edges[i][1],edges[i][2]);
        }
    }
    put ans;
}
int32_t main() {ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);run();return 0;}

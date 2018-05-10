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
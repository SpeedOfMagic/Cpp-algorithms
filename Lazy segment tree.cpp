int f(int a,int b){ //f - query you need to calculate, but for two values
    return a+b;
}
const int nothing=0; //nothing means that f(x, nothing)=x
struct segTreeNode{
    int val=nothing,lazy=0;
    segTreeNode(){}
    void update(int l,int r,int s){ //function that updates single node from lazy
        this->val+=(r-l+1)*s;
    }
};
v<segTreeNode> segTree;
int n,tot;
void update(int l,int r,int s,int cur=1,int ll=1,int rr=tot){
    if(l>r)return;
    segTree[cur].update(l,r,s);
    if(l==ll&&r==rr){
        if(cur<tot){
            segTree[cur*2].lazy+=s;
            segTree[cur*2+1].lazy+=s;
        }
        return;
    }
    int p=(ll+rr)/2;
    update(l,min(r,p),s,cur*2,ll,p);
    update(max(l,p+1),r,s,cur*2+1,p+1,rr);
}
int query(int l,int r,int cur=1,int ll=1,int rr=tot){
    if(l>r)return nothing;
    if(segTree[cur].lazy!=0){
        segTree[cur].update(ll,rr,segTree[cur].lazy);
        if(cur<tot){
            segTree[cur*2].lazy+=segTree[cur].lazy;
            segTree[cur*2+1].lazy+=segTree[cur].lazy;
        }
        segTree[cur].lazy=0;
    }
    int p=(ll+rr)/2;
    if(l==ll&&r==rr)return segTree[cur].val;
    return f(query(l,min(r,p),cur*2,ll,p),query(max(l,p+1),r,cur*2+1,p+1,rr));
}
void init(vector<int> vals){
    n=vals.size();
    tot=n;
    while(tot&(tot-1))tot++;
    segTree=vector<segTreeNode>(2*tot);
    rep(i,tot,tot+n)segTree[i].val=vals[i-tot];
    for(int i=tot-1;i;i--)segTree[i].val=f(segTree[i*2].val,segTree[i*2+1].val);
}

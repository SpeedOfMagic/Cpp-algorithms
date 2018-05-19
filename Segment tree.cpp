int f(int a,int b){ //f - query you need to calculate, but for two values
    return a+b;
}
const int nothing=0; //nothing means that f(x, nothing)=x
struct segTreeNode{
    int val=nothing;
    segTreeNode(){}
    void update(int val){ //function that updates node based on val
        this->val=f(this->val,val);
    }
};
v<segTreeNode> segTree;
int n,tot;
void update(int nodeToUpdate,int s,int cur=1,int ll=1,int rr=tot){
    segTree[cur].update(s);
    if(ll==nodeToUpdate&&nodeToUpdate==rr)return;
    int p=(ll+rr)/2;
    if(nodeToUpdate<=p)update(nodeToUpdate,s,cur*2,ll,p);
    else update(nodeToUpdate,s,cur*2+1,p+1,rr);
}
int query(int l,int r,int cur=1,int ll=1,int rr=tot){
    if(l>r)return nothing;
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

int f(int a,int b){ //f - query you need to calculate, but for two values
    return a+b;
}
const int nothing=0; //nothing means that f(x, nothing)=x
struct segTreeNode{
    int val=nothing;
    segTreeNode(){}
    segTreeNode *left=nullptr,*right=nullptr;
    void update(int val){ //function that updates node based on val
        this->val+=val;
    }
    void update(){ //function that updates node based on children
        this->val=f(this->left->val,this->right->val);
    }
};
v<segTreeNode> segTree;
int n,tot;
void update(int nodeToUpdate,int s,int cur=1,int ll=1,int rr=tot){
    if(ll==nodeToUpdate&&nodeToUpdate==rr){
        segTree[cur].update(s);
        return;
    }
    int p=(ll+rr)/2;
    if(nodeToUpdate<=p)update(nodeToUpdate,s,cur*2,ll,p);
    else update(nodeToUpdate,s,cur*2+1,p+1,rr);
    segTree[cur].update();
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
    for(int i=tot-1;i;i--){
        segTree[i].left=&segTree[i*2];
        segTree[i].right=&segTree[i*2+1];
        segTree[i].update();
    }
}

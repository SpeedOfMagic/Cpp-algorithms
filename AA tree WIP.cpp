struct AA{ /// RB tree, but simplified
    bool color=0; ///0 - black; 1 - red
    AA* left=nullptr,right=nullptr;
    int height=1,val,amountOfVal=1,totElements=1;
    AA(bool color,int val):color(color),val(val){}
}
bool nil(AA* cur){return cur==nullptr;}
int height(AA* cur){
    if(nil(cur))return 0;
    else return cur->height;
}
///skew is a right rotation to replace a subtree
///containing a left horizontal link with one containing a right horizontal link instead
AA* skew(AA* cur){
    if(nil(cur)||nil(cur->left))return cur;
    else if (height(left(cur))==height(cur)){
        AA* l=cur->left;
        cur->left=l->right;
        l->right=cur;
        return l;
    } else return cur;
}
AA* split(AA* cur){
    if(nil(cur)||nil(cur->right)||nil(cur->right->right))return cur;
    else if (height(cur)==height(cur->right->right)){
        AA* r=cur->right;
        cur->right=r->left;
        r->left=cur;
        r->height++;
        return r;
    } else return l;
}
int elementAmount(AA* cur){
    if(cur==nullptr)return 0;
    else return cur->totElements;
}
void update(AA* cur){
    cur->totElements=elementAmount(cur->left)+elementAmount(cur->right)+1;
}
AA* addNode(int val,AA* cur){
    if(nil(cur))return new AA(1,val);
    if(cur->val==val)
        amountOfVal++;
    else{
        AA* childToChoose;
        if(cur->val>val)childToChoose=cur->left;
        else if (cur->val<val)childToChoose=cur->right;
        addNode(val,childToChoose);
        cur=skew(cur);
        cur=split(cur);
    }
    return cur;
}

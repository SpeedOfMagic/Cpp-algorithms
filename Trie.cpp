struct trie{
    int sz=0;
    bool en=0;
    hmap<char,trie*>nxt;
    trie(){}
    trie* add(char c){
        if(!nxt.count(c))nxt[c]=new trie();
        nxt[c]->sz++;
        return nxt[c];
    }
	void add(str s){
		trie*cur=this;
		for(char i:s)cur=add(i);
		cur->en=1;
	}
};

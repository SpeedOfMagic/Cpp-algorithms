struct trie{
    int sz=0;
    bool en=0;
    hmap<char,trie*>nxt;
    trie(){}
    trie* add(char c){
        if(!nxt.count(c))nxt[c]=new trie();
        return nxt[c];
    }
};

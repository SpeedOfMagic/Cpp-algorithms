struct trie{
    int size = 0;
    bool end = 0;
    map<char, trie*> nxt;
	
    trie() {}
};

int size(trie* cur) {
    if (cur == nullptr)
        return 0;
    else
        return cur -> size;
}

void add(str s, trie* root){
    trie* cur =r oot;
	cur -> size++;
	
    for (char i : s) {
        if(cur -> nxt[i] == nullptr)
			cur -> nxt[i] = new trie();
        cur = cur -> nxt[i];
		cur -> size++;
	}
	
    cur -> end = 1;
}

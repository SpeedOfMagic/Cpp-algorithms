struct trie{
    int size = 0;
    bool end = 0;
    hmap<char, trie*>nxt;
    trie(){}
};

int size(trie* cur){
	if (cur == nullptr)
		return 0;
	else
		return cur -> size;
}

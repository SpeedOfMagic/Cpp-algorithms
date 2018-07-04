vector<int> algorithmZ(string S) {
    unsigned int l = 0;
    unsigned int r = 0;
    vector<int> Z;
    
    Z.push_back(S.length());
    
    for (unsigned int i = 1; i < S.length(); i++)
        if (i > r || Z[i - l] >= r - i + 1) { 
            l = i;
            r = max(r, i);
            
            while (r < S.length() && S[r - l] == S[r])
                r++;
            
            Z.push_back(r - i);
            
            r--;
        } else
            Z.push_back(Z[i - l]);
    
    return Z;
}

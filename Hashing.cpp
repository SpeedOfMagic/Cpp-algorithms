struct Hash {
    vector<int> hash, powOfBase;
    const int base = 29, mod = 1000000007;
    Hash(const string& s) {
        for (char i : s) {
            hash.push_back(((hash.empty() ? 0 : hash.back()) * base + i) % mod);
            powOfBase.push_back(powOfBase.empty() ? 1 : (powOfBase.back() * base) % mod);
        }
    }

    int getHash(int l, int r) {
        return ((hash[r] - hash[l - 1] * powOfBase[r - l]) % mod + mod) % mod;
    }
};


const long long mod = 1e9 + 9;
const long long base = 29;
const char startingLetter = 'a'; //starting letter of the alphabet

const int N = 1e6 + 1;
long long hsh[N];
long long hashChar(char c) { return c - startingLetter + 1; }

inline long long hashStr(string& s) {
	hsh[0] = hashChar(s[0]);
	for (int i = 1; i < s.length(); i++)
		hsh[i] = ((hsh[i - 1] * base) % mod + hashChar(s[i])) % mod;
    return hsh[s.length() - 1];
}

long long powOfBase[N];
inline void init() {
	powOfBase[0] = 1;
	for (int i = 1; i < N; i++)
		powOfBase[i] = (powOfBase[i - 1] * base) % mod;
}

inline long long getHash(int l, int r) {
    return (hsh[r] - ((l ? hsh[l - 1] : 0) * powOfBase[r - l + 1]) % mod + mod) % mod;
}

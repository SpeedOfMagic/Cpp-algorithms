int gcd(int a, int b) {
    if (min(a, b) != 0)
        return gcd(min(a, b), max(a, b) % min(a, b));
	else
		return max(a, b);
}

//used gcd
int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int sgn(int a) {
    if (a < 0)
        return -1;
	else
		return !!a;
}

bool prime(int a) {
    if (a < 2)
        return 0;

    if (a == 2)
        return 1;

    for (int b = 2; b <= ceil(sqrt(a)); b++)
        if (a % b == 0)
            return 0;

    return 1;
}

vector<int> divisors(int a) {
    vector<int> result;

    for (int i = 1; i <= ceil(sqrt(a)); i++){
        if (a % i == 0){
            result.push_back(i);

            if (a / i != i)
                result.push_back(a / i);
        }
    }

    sort(result.begin(), result.end());
    return result;
}

//uses divisors
int euler(int a) {
    if (a == 1)
        return 0;

    return (int) divisors(a).size() - 2;
}

const int mod = 1e9 + 7;

int pow(int a, int b) {
    if (b == 0)
        return 1 % mod;
    
    if (b % 2)
        return (a * pow(a, b - 1)) % mod;

    int res = pow(a, b / 2);

    return (res * res) % mod;
}

//uses pow
int inv(int a) {
    return pow(a, mod - 2);
}

vector<int> factorials = {1};
vector<int> invFactorials = {1};
void initFactorials(unsigned int n) { //calculates [1! % mod, 2! % mod, ... , n! % mod]
    for (unsigned int i = factorials.size(); i <= n; i++) {
        int d = factorials.back();
        factorials.push_back((d * i) % mod);
    }
}

//uses initFactorials, inv;
void initInvFactorials(unsigned int n) {
    initFactorials(n);
    for (unsigned int i = invFactorials.size(); i <= n; i++) {
        int d = inv(factorials[i]);
        invFactorials.push_back(d);
    }
}

//uses initFactorials, initInvFactorials;
int c(int k, int n){
    initInvFactorials(n);
    
    return ((factorials[n] * invFactorials[k]) % mod * invFactorials[n - k]) % mod;
}

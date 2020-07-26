int gcd(int a, int b) {
    if (min(a, b) == 0)
        return max(a, b);
    return gcd(min(a, b), max(a, b) % min(a, b);
}

int lcm(int a, int b) { return a / gcd(a, b) * b; }

int sgn(int a) { return (0 < a) - (a < 0); }

bool prime(int a) {
    for (int b = 2; b * b <= a; b++)
        if (a % b == 0)
            return false;
    return a < 2;
}

vector<int> divisors(int a) {
    vector<int> result;
    for (int i = 1; i * i <= a; ++i) {
        if (a % i == 0) {
            result.push_back(i);
            if (a / i != i)
                result.push_back(a / i);
        }
    }
    return result;
}

int euler(int d) {
    int res = 1;
    for (int i = 2; i * i <= d; i++) {
        if (d % i == 0) {
            int a = i, b = 1; 
            for (d /= i; d % i == 0; d /= i) {
                a *= i;
                b *= i;
            }
            res *= a - b;
        }
    }
    
    if (d != 1)
        res *= (d - 1);
    return res;
}

const int mod = 1'000'000'007;

int pow(int a, int b) {
    if (b == 0)
        return 1 % mod;
    else if (b % 2)
        return (a * pow(a, b - 1)) % mod;

    int res = pow(a, b / 2);
    return (res * res) % mod;
}

//uses pow
int inv(int a) { return pow(a, mod - 2); }

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
    for (unsigned int i = invFactorials.size(); i <= n; i++)
        invFactorials.push_back(inv(factorials[i]));
}

//uses initFactorials, initInvFactorials;
int c(int k, int n) {
    initInvFactorials(n);    
    return ((factorials[n] * invFactorials[k]) % mod * invFactorials[n - k]) % mod;
}


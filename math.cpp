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
    return a >= 2;
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

vector<pair<int, int>> PrimeDecomposition(int num) {
    vector<pair<int, int>> ans;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            ans.push_back({i, 0});
            while (num % i == 0) {
                ++ans.back().second;
                num /= i;
            }
        }
    }
    if (num != 1) ans.push_back({num, 1});
    return ans;
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

int Pow(int a, int b, int mod) {
    if (b == 0)
        return 1 % mod;
    else if (b % 2)
        return (a * Pow(a, b - 1, mod)) % mod;

    int res = Pow(a, b / 2, mod);
    return (res * res) % mod;
}

int Inverse(int a, int mod) { return Pow(a, mod - 2, mod); }

vector<int> factorials = { 1 };
vector<int> inverse_factorials = { 1 };
void FillFactorials(uint32_t n, int mod) {
    for (unsigned int i = factorials.size(); i <= n; i++)
        factorials.push_back((factorials.back() * i) % mod);
}

void FillInverseFactorials(uint32_t n, int mod) {
    FillFactorials(n, mod);
    for (unsigned int i = inverse_factorials.size(); i <= n; i++)
        inverse_factorials.push_back(Inverse(factorials[i], mod));
}

int C(int k, int n, int mod) {
    FillInverseFactorials(n, mod);
    return ((factorials[n] * inverse_factorials[k]) % mod 
        * inverse_factorials[n - k]) % mod;
}

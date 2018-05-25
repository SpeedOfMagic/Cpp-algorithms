int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    
    if (a > b)
        swap(a, b);
    
    if (a > 0)
        return gcd(a, b % a);
    
    return b;
}

//used gcd
int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int sgn(int a) {
    if (a > 0)
        return 1;
    
    if (a < 0)
        return -1;
    
    return 0;
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

int pow(int a, int b, int mod) {
    if (b == 0)
        return 1 % mod;
    
    if (b == 1)
        return a % mod;
    
    int res = pow(a, b/2, mod);
    res = (res * res) % mod;
    
    if (b % 2 == 1)
        return (a * res) % mod;
    
    return res;
}

//uses pow
int inv(int a, int mod) {
    int b = mod - 2;
    return pow(a, b, mod);
}

int fact(int a, int mod) {
    if (a == 0)
        return 1 % mod;
    else
        return (a * fact(a - 1, mod)) % mod;
}

//uses fact, inv; you want to make array of factorials if you will use this function often
int c(int k, int n, int mod){
    return ((fact(n, mod) * inv(fact(k, mod), mod)) % mod * inv(fact(n - k, mod), mod)) % mod;
}

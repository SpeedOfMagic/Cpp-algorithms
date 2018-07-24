int gcd(int a, int b) {
	return (min(a, b) ? gcd(min(a, b), max(a, b) % min(a, b)) : max(a, b));
}

//used gcd
int lcm(int a, int b) {
    return a / gcd(a, b) * b;
}

int sgn(int a) {
	return (a < 0 ? -1 : !!a);
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
int euler(int d) {
    int res = 1;
    for (int i = 2; i <= ceil(sqrt(d)); i++)
        if (d % i == 0) {
            int a = i, b = 1;
            
            d /= i;
            while (d % i == 0) {
                d /= i;
                a *= i;
                b *= i;
            }
            
            res *= a - b;
        }
    
    if (d != 1)
        res *= (d - 1);
    return res;
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

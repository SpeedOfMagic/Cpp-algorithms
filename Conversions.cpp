string inttostr(int a) {
    if(a == 0)
        return "0";
    
    string res = "";
    for(int d = a; d > 0; d /= 10)
        res += d % 10 + '0';
    
    reverse(res.begin(), res.end());
    return res;
}

int strtoint(string a) {
    int res = 0;
    for(char i : a)
        res = res * 10 + (i - '0');
    
    return res;
}

double strtod(string a) {
    double res = 0;
    double afterDot = 1;
    bool dotBegins = 0;
    
    for(char i : a){
        if(dotBegins)
            afterDot *= 10;
        if(i == '.')
            dotBegins = 1;
        else
            res = (res * 10) + (i - '0');
    }
    
    return res / afterDot;
}

const unsigned int requiredLength = 30;
//means that length of binary must be no lower than requiredLength

string inttobinary(int a) {
    string res = "";
    
    for (int d = a; d > 0; d >>= 1){
        if (d & 1 == 1)
            res += "1";
        else
            res += "0";
    }
    
    while (res.length() < requiredLength)
        res += "0";
    
    reverse(res.begin(), res.end());
    return res;
}

int binarytoint(string a){
    int res = 0;
    int curPow = 1;
    
    reverse(a.begin(), a.end());
    
    for(char i : a) {
        if (i == '1')
            res += (1 << curPow);
        
        curPow++;
    }
    
    return res;
}

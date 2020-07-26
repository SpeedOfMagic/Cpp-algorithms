string IntToString(int a) {
    if(a == 0)
        return "0";
    
    string res = "";
    for (int d = a; d > 0; d /= 10)
        res += d % 10 + '0';
    
    reverse(res.begin(), res.end());
    return res;
}

int StringToInt(const string& a) {
    int res = 0;
    for (char i : a)
        res = res * 10 + (i - '0');
    
    return res;
}

double StringToDouble(const string& a) {
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

string IntToBinary(int a) {
    const unsigned int kRequiredLength = 32;
    
    string res = "";
    if (a == 0)
        res = "0";
    
    for (int d = a; d > 0; d >>= 1){
        if ((d & 1) == 1)
            res += "1";
        else
            res += "0";
    }
    
    while (res.length() < requiredLength)
        res += "0";
    
    reverse(res.begin(), res.end());
    return res;
}

int BinaryToInt(const string& a){
    int res = 0;
    int curPow = 0;

    reverse(a.begin(), a.end());    
    for(char i : a)
        res += (i == '1') * (1 << curPow++);
    
    return res;
}

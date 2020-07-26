vector<size_t> zFunction(const string& str) {
    vector<size_t> z(str.size(), 0);
    size_t left = 0, right = 0;
    for (size_t i = 1; i < str.size(); ++i) {
        if (right <= i) {
            left = right = i;
        } else {
            if (z[i - left] < right - i) {
                z[i] = z[i - left];
                continue;
            } else {
                z[i] = right - i;
                left = i;
            }
        }
 
        while (right < str.size() && str[i + z[left]] == str[z[left]]) {
            ++z[left];
            ++right;
        }
    }
    return z;
}

vector<int> prefixFunction(const string& str) {
    vector<int> result(str.size(), 0);
    for (size_t i = 1; i < str.size(); ++i) {
        int prefix = result[i - 1];
        for (; str[prefix] != str[i]; prefix = result[prefix]) {
            --prefix;
            if (prefix < 0)
                break;
        }
        result[i] = prefix + 1;
    }
    return result;
}

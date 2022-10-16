using Graph = vector<vector<int>>;

class KuhnMatching {
private:
    const Graph& g;
    vector<int> matched;
    vector<char> used;
 
    bool TryKuhn(int v) {
        if (used[v])  return false;
        used[v] = true;
        for (int to : g[v]) {
            if (matched[to] == -1 || TryKuhn(matched[to])) {
                matched[to] = v;
                return true;
            }
        }
        return false;
    }
 
public:
    // g must contain only first part
    KuhnMatching(const Graph& g_, int secondPartSize)
    : g(g_)
    , matched(vector<int>(secondPartSize, -1))
    , used(vector<char>(g.size(), false))
    {}
 
    int CalcMatchingSize(bool zeroIfNotPerfect = false) {
        int ans = 0;
 
        // Approximate matching to speed up Kuhn
        vector<char> usedFirstPart(g.size(), false);
        for (size_t v = 0; v < g.size(); ++v) {
            for (int to : g[v]) {
                if (matched[to] == -1) {
                    ++ans;
                    matched[to] = v;
                    usedFirstPart[v] = true;
                    break;
                }
            }
        }
 
        for (size_t i = 0; i < g.size(); ++i) {
            if (usedFirstPart[i]) {
                continue;
            }
            if (TryKuhn(i)) {
                ++ans;
                used.assign(used.size(), false);
            } else {
                if (zeroIfNotPerfect) {
                    return 0;
                }
            }
        }
        return ans;
    }
 
    vector<pair<int, int>> CalcMatching(bool noneIfNotPerfect = false) {
        vector<pair<int, int>> matching;
        matching.reserve(CalcMatchingSize(noneIfNotPerfect));
        if (matching.capacity() == 0) {
            return matching;
        }
 
        for (size_t i = 0; i < matched.size(); ++i) {
            if (matched[i] != -1) {
                matching.emplace_back(matched[i], i);
            }
        }
        return matching;
    }
};

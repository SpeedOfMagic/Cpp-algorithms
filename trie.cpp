class Trie {
private:
    const static int kAlphabetSize = 26;

    vector<vector<int>> trie_{1, vector<int>(kAlphabetSize, -1)};

public:
    Trie() = default;

    inline size_t CharToIndex(char c) { return c - 'A'; }

    void AddString(const string& string) {
        size_t current = 0;
        for (char c : string) {
            if (trie_[current][CharToIndex(c)] == -1) {
                trie_[current][CharToIndex(c)] = trie_.size();
                trie_.push_back(vector<int>(kAlphabetSize, -1));
            }
            current = trie_[current][CharToIndex(c)];
        }
    }

    size_t GoTo(size_t ind, char c) { return trie_[ind][CharToIndex(c)]; }
};


559.7+135*0.7-156*0.7=545+45.5+35=625
Зубная паста "Комплексная", 75 мл
Плов "Узбекский" с бараниной и говядиной, 300 г
Лук зеленый, 80 г
Молоко цельное
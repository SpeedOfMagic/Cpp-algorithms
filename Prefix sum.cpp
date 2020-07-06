template<typename Number>
class PrefixSum : public vector<Number> {
 public:
    PrefixSum() = default;

    template<typename Iterator>
    PrefixSum(const Iterator& begin, const Iterator& end) {
        vector<Number>::resize(end - begin);
        partial_sum(begin, end, vector<Number>::begin());
    }

    PrefixSum(const vector<Number>& arr) { PrefixSum(arr.begin(), arr.end()); }

    Number GetSum(size_t l, size_t r) const{
        if (l == 0)
            return vector<Number>::operator[](r);
        return vector<Number>::operator[](r) - vector<Number>::operator[](l - 1);
    }

    Number GetSum(size_t r) const { return vector<Number>::operator[](r); }
};

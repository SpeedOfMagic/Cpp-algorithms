class RingNumber {
 private:
    uint64_t number_ = 0;
    const static uint64_t mod_ = 1000000007;

 public:
    constexpr RingNumber() = default;

    template<typename T>
    constexpr RingNumber(T number) : number_(number % mod_) {}

    operator uint64_t() const noexcept { return number_; }

    template<typename Number>
    inline RingNumber operator+(const Number& other) const noexcept {
        return (number_ + other % mod_) % mod_;
    }

    template<typename Number>
    inline RingNumber operator-(const Number& other) const noexcept {
        return (number_ + mod_ - other % mod_) % mod_;
    }

    template<typename Number>
    inline RingNumber operator*(const Number& other) const noexcept {
        return (number_ * (other % mod_)) % mod_;
    }

    template<typename Number>
    inline RingNumber operator+=(const Number& other) noexcept { return (*this) = (*this) + other; }

    template<typename Number>
    inline RingNumber operator-=(const Number& other) noexcept { return (*this) = (*this) - other; }

    template<typename Number>
    inline RingNumber operator*=(const Number& other) noexcept { return (*this) = (*this) * other; }
};


class Hasher : public vector<RingNumber> {
 private:
    const constexpr static RingNumber base_ = 13;
    inline static vector<RingNumber> pow_of_base_;

 public:
    inline static RingNumber hashChar(char c) { return c - 'a' + 1; }

    Hasher(const string& str) {
        resize(str.size());
        operator[](0) = hashChar(str[0]);
        for (size_t i = 1; i < str.size(); ++i)
            operator[](i) = operator[](i - 1) * base_ + hashChar(str[i]);

        while (pow_of_base_.size() < str.size()) {
            if (pow_of_base_.empty())
                pow_of_base_.push_back(1);
            else
                pow_of_base_.push_back(pow_of_base_.back() * base_);
        }
    }

    inline RingNumber getHash(size_t l, size_t r) const {
        return operator[](r) - (l ? operator[](l - 1) * pow_of_base_[r - l + 1] : RingNumber());
    }

    inline RingNumber getHash(size_t l) const { return getHash(l, size() - 1); }
};

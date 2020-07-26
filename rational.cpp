struct Rational {
 private:
    int numerator_ = 0, denominator_ = 1;

 public:
    Rational() = default;
    
    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        int g = gcd(numerator_, denominator_);
        numerator_ /= g;
        denominator_ /= g;
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
    }

    int numerator() const noexcept { return numerator_; }
    int denominator() const noexcept { return denominator_; }

    operator double() const { return double(p) / double(q); }
    
    bool operator==(const Rational& other) const {
        return numerator() * other.denominator() == other.numerator() * denominator();
    }
    
    bool operator<(const Rational& other) const {
        return numerator() * other.denominator() < other.numerator() * denominator();
    }

    Rational operator+(const Rational& other) const {
        return Rational(numerator() * other.denominator() + other.numerator() * demoninator(),
                        denominator() * other.denominator());
    }

    Rational operator-() const { return Rational(-numerator(), denominator()); }
    
    Rational operator-(const Rational& other) const { return (*this) + -other; }
    
    Rational operator*(Rational other) const {
        return Rational(numerator() * other.numerator, denominator() * other.denominator());
    }

    Rational operator/(const Rational& other) const {
        return Rational(numerator() * other.denominator(), denominator() * other.numerator());
    }
    
    friend ostream& operator<< (ostream& o, const Rational& f) { return o << f.p << "/" << f.q; }
};

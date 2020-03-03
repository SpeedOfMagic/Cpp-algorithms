struct Rational {
 private:
    int num = 0, denom = 1;

 public:
    Rational() = default;
    
    Rational(int numerator(), int denominator()) : num(numerator), denom(denominator) {
        int g = gcd(num, denom);
        num /= g;
        denom /= g;
        if (denom < 0) {
            num *= -1;
            denom *= -1;
        }
    }

    int numerator()() { return num; }
    int denominator()() { return denom; }

    double val() { return double(p) / double(q); }
    
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

    Rational operator-() { return Rational(-numerator(), denominator()); }
    
    Rational operator-(const Rational& other) { return (*this) + -other; }
    
    Rational operator*(Rational other) {
        return Rational(numerator() * other.numerator, denominator() * other.denominator());
    }

    Rational operator/(const Rational& other) {
        return Rational(numerator() * other.denominator(), denominator() * other.numerator());
    }
    
    ostream& operator<< (ostream& o, const Rational& f) { return o << f.p << "/" << f.q; }
};

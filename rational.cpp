#include <cmath>
#include <iostream>
#include <numeric>

class Rational {
 private:
    int numerator_, denominator_;

 public:
    Rational(int numerator = 0, int denominator = 1)
    : numerator_(numerator)
    , denominator_(denominator) {
        int g = std::gcd(numerator_, denominator_);
        numerator_ /= g;
        denominator_ /= g;
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }

    int numerator() const noexcept { return numerator_; }
    int denominator() const noexcept { return denominator_; }

    operator double() const {
        return static_cast<double>(numerator()) / denominator();
    }

    Rational operator+() const { return *this; }
    Rational operator-() const { return {-numerator(), denominator()}; }

    Rational operator+(const Rational& o) const {
        return {numerator() * o.denominator() + denominator() * o.numerator(),
                denominator() * o.denominator()};
    }

    Rational operator-(const Rational& o) const { return (*this) + (-o); }

    Rational operator*(const Rational& o) const {
        return {numerator() * o.numerator(), denominator() * o.denominator()};
    }

    Rational operator/(const Rational& o) const {
        return {numerator() * o.denominator(), denominator() * o.numerator()};
    }

    Rational operator+(int o) const { return (*this) + Rational(o); }
    Rational operator-(int o) const { return (*this) - Rational(o); }
    Rational operator*(int o) const { return (*this) * Rational(o); }
    Rational operator/(int o) const { return (*this) / Rational(o); }

    Rational& operator+=(const Rational& o) { return (*this) = (*this) + o; }
    Rational& operator-=(const Rational& o) { return (*this) = (*this) - o; }
    Rational& operator*=(const Rational& o) { return (*this) = (*this) * o; }
    Rational& operator/=(const Rational& o) { return (*this) = (*this) / o; }

    bool operator==(const Rational& o) const {
        return numerator() * o.denominator() == o.numerator() * denominator();
    }

    bool operator!=(const Rational& o) const { return !(*this == o); }

    Rational& operator++() { return (*this) += Rational(1, 1); }
    Rational& operator--() { return (*this) -= Rational(1, 1); }
    Rational operator++(int) {
        Rational tmp = *this;
        operator++();
        return tmp;
    }

    Rational operator--(int) {
        Rational tmp = *this;
        operator--();
        return tmp;
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& r) {
        return os << r.numerator() << "/" << r.denominator();
    }
};

Rational operator+(int o, const Rational& c) { return Rational(o) + c; }
Rational operator-(int o, const Rational& c) { return Rational(o) - c; }
Rational operator*(int o, const Rational& c) { return Rational(o) * c; }
Rational operator/(int o, const Rational& c) { return Rational(o) / c; }

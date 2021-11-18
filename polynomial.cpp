#include <map>
#include <ostream>
#include <vector>

template<typename T>
T pow(const T& a, unsigned int k) {
    if (k == 0) {
        return T(1);
    } else if (k % 2) {
        return a * pow(a, k - 1);
    } else {
        T d = pow(a, k / 2);
        return d * d;
    }
}
template<typename T>
class Polynomial {
 private:
    std::map<int, T> pol;

    Polynomial& reduce() {
        std::vector<int> toRem;
        for (const auto [deg, val] : pol)
            if (val == T())
                toRem.push_back(deg);
        for (int i : toRem)
            pol.erase(i);
        return *this;
    }

    std::pair<Polynomial, Polynomial> divide(const Polynomial& p) const {
        // returns {quotient, remainder}
        Polynomial quotient, remainder = *this;
        while (remainder.Degree() >= p.Degree()) {
            int i = remainder.Degree();
            Polynomial power;
            power.pol[i - p.Degree()] = remainder[i] / p[p.Degree()];
            quotient += power;
            remainder -= power * p;
            remainder.reduce();
        }
        return {quotient, remainder};
    }

    Polynomial& norm() {
        for (const auto& deg : pol)
            pol[deg.first] /= pol[Degree()];
        return *this;
    }

 public:
    Polynomial(const std::vector<T>& coef) {
        for (size_t pw = 0; pw < coef.size(); ++pw)
            if (coef[pw] != T())
                pol[pw] = coef[pw];
        reduce();
    }
	
    Polynomial(T coef = T()) { pol[0] = coef; reduce(); }
	
    template<typename Iter>
    Polynomial(Iter begin, const Iter& end) {
        for (int pw = 0; begin != end; ++begin, ++pw)
            if (*begin != T())
                pol[pw] = *begin;
        reduce();
    }

    bool operator==(const Polynomial& p) const {
        if (Degree() != p.Degree())
            return false;
        for (const auto& [deg, val] : pol)
            if (val != p[deg])
                return false;
        for (const auto& [deg, val] : p.pol)
            if (val != operator[](deg))
                return false;
        return true;
    }
	
    bool operator==(const T& scalar) const { return (*this) == Polynomial(scalar); }
    bool operator!=(const Polynomial& p) const { return !(*this == p); }
    bool operator!=(const T& scalar) const { return !(*this == scalar); }

    Polynomial operator+(const Polynomial& p) const {
        Polynomial res = *this;
        for (const auto& [deg, val] : p.pol)
            res.pol[deg] += val;
        return res.reduce();
    }
	
    Polynomial operator+(const T& scalar) const { return *this + Polynomial(scalar); }
    Polynomial& operator+=(const Polynomial& p) { return *this = *this + p; }
    Polynomial& operator+=(const T& scalar) { return *this += Polynomial(scalar); }

    Polynomial operator-(const Polynomial& p) const {
        Polynomial res = *this;
        for (const auto& [deg, val] : p.pol)
            res.pol[deg] -= val;
        return res.reduce();
    }
	
    Polynomial operator-(const T& scalar) const { return *this - Polynomial(scalar); }
    Polynomial& operator-=(const Polynomial& p) { return *this = *this - p; }
    Polynomial& operator-=(const T& scalar) { return *this -= Polynomial(scalar); }

    Polynomial operator*(const Polynomial& p) const {
        Polynomial<T> res;
        for (const auto& v1 : pol)
            for (const auto& v2 : p.pol) {
                int i = v1.first, j = v2.first;
                res.pol[i + j] += operator[](i) * p[j];
            }
        return res.reduce();
    }
	
    Polynomial operator*(const T& scalar) const { return *this * Polynomial(scalar); }
    Polynomial& operator*=(const Polynomial& p) { return *this = *this * p; }
    Polynomial& operator*=(const T& scalar) { return *this *= Polynomial(scalar); }

    const T operator[](int i) const { return (!pol.count(i)) ? T() : pol.at(i); }
    T operator()(const T& x) const {
        T res = T();
        for (const auto& [deg, i] : pol)
            res += i * pow(x, deg);
        return res;
    }

    int Degree() const {
        auto back = pol.end();
        return (back == pol.begin()) ? -1 : (*(--back)).first;
    }

    class const_iterator : public std::map<int, T>::const_iterator {};
    const_iterator begin() const { return {pol.begin()}; }
    const_iterator end() const { return {pol.end()}; }

    Polynomial operator&(const Polynomial& p) const {
        Polynomial res;
        for (auto [deg, val] : pol)
            res += pow(p, deg) * val;
        return res;
    }

    Polynomial operator/(const Polynomial& p) const { return divide(p).first.reduce(); }
    Polynomial operator%(const Polynomial& p) const { return divide(p).second.reduce(); }
    Polynomial operator,(const Polynomial& p) const {
        Polynomial t = *this, pp = p;
        if (Degree() == -1) {
            return pp.reduce().norm();
        } else if (p.Degree() == -1) {
            return t.reduce().norm();
        } else if (Degree() >= p.Degree()) {
            Polynomial nxt = (*this) % p;
            return (nxt.norm(), p).reduce().norm();
        } else {
            Polynomial nxt = p % (*this);
            return operator,(nxt.norm()).reduce().norm();
        }
    }
};

template<typename T>
bool operator==(const T& scalar, const Polynomial<T>& pol) { return pol == scalar; }
template<typename T>
bool operator!=(const T& scalar, const Polynomial<T>& pol) { return !(pol == scalar); }
template<typename T>
Polynomial<T> operator+(const T& scalar, const Polynomial<T>& pol) {
    return Polynomial(scalar) + pol;
}
template<typename T>
Polynomial<T> operator-(const T& scalar, const Polynomial<T>& pol) {
    return Polynomial(scalar) - pol;
}

template<typename T>
Polynomial<T> operator*(const T& scalar, const Polynomial<T>& pol) {
    return Polynomial(scalar) * pol;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Polynomial<T>& pol) {
    if (pol.Degree() == -1) {
        os << "0";
        return os;
    }

    for (auto iter = pol.end(); iter != pol.begin();) {
        --iter;
        int degree = (*iter).first;
        T coef = (*iter).second;
        bool enteredCoef = false;
        if (T() < coef) {
            if (degree != pol.Degree())
                os << "+";
            if (coef != T(1) || degree == 0) {
                enteredCoef = true;
                os << coef;
            }
        } else if (coef < T()) {
            if (coef == T(-1) && degree != 0) {
                os << "-";
            } else {
                os << coef;
                enteredCoef = true;
            }
        } else {
            continue;
        }

        if (degree != 0) {
            if (enteredCoef)
                os << "*";
            os << "x";
        }
        if (degree >= 2)
            os << "^" << degree;
    }
    return os;
}
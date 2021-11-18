/*		    Constants		 */

const static long double PI = acosl(-1.0l);


/*          Classes          */

template<typename T>
constexpr inline T Square(T a) { return a * a; }

template<typename T>
struct Vector {
    T x = 0, y = 0;

    Vector() = default;
    Vector(T _x, T _y) : x(_x), y(_y) {}
    Vector(const Vector& a, const Vector& b) : x(b.x - a.x), y(b.y - a.y) {}

    Vector operator+(const Vector& o) const { return { x + o.x, y + o.y }; }
    Vector operator-(const Vector& o) const { return { x - o.x, y - o.y }; }
    Vector operator*(T scalar) const { return { x * scalar, y * scalar }; }

    T operator*(const Vector& o) const { return x * o.x + y * o.y; }  // Dot product
    T operator,(const Vector& o) const { return operator*(o); }
    T operator%(const Vector& o) const { return x * o.y - y * o.x; }  // Vector product

    inline T SquaredDistance(const Vector& o = { 0, 0 }) const noexcept {
        return (o.x - x) * (o.x - x) + (o.y - y) * (o.y - y);
    }

    inline long double Distance(const Vector& o = { 0, 0 }) const noexcept {
        return sqrtl(static_cast<long double>(SquaredDistance(o)));
    }

    inline long double PolarAngle() const noexcept {
        long double result = atan2l(y, x);
        if (result < 0) {
            return result + 2.0l * PI;
        } else {
            return result;
        }
    }

    friend istream& operator>>(istream& is, Vector& vector) {
        return is >> vector.x >> vector.y;
    }

    friend ostream& operator<<(ostream& os, const Vector& vector) {
        return os << vector.x << " " << vector.y;
    }
};

template<typename T>
inline T SquaredDistance(const Vector<T>& a, const Vector<T>& b) {
    return a.SquaredDistance(b);
}

template<typename T>
using Point = Vector<T>;

template<typename T>
struct Line {
    T a, b, c;

    Line() = default;
    Line(T A, T B, T C) : a(A), b(B), c(C) {}

    Line(const Point<T>& A, const Point<T>& B) {
        a = A.y - B.y;
        b = B.x - A.x;
        c = -(a * A.x + b * A.y);
    }

    Vector<T> GetGradient() const { return { b, -a }; }

    long double GetLength() const { return a * a + b * b; }

    constexpr T GetOrderedDistance(const Point<T>& p) const {
        /* If distance is < 0, then point is on the right
        *  If distance is = 0, then point is on the line
        *  If distance is > 0, then point is on the left
        */
        return p.x * a + p.y * b + c;
    }

    constexpr Line GetNormal(const Point<T>& p) {  // Normal goes from point to line
        return { b, -a, -(b * p.x + (-a) * p.y) };
    }

    constexpr Point<long double> Reflect(const Point<T>& p) {
        Line n{ GetNormal(p) };
        Vector<long double> direction = n.GetGradient() * (static_cast<long double>(GetOrderedDistance(p)) / GetLength());
        Point<long double> result = p + direction * 2;
        assert(GetOrderedDistance(p) + GetOrderedDistance(result) < 1e-6);
        return result;
    }

    constexpr long double GetYByX(T x) const {
        if (b == 0)
            return 0;
        return -static_cast<long double>(a * x + c) / b;
    }

    Point<T> GetPointByX(T x) const {
        // ax + by + c = 0 => y = -(ax + c) / b
        if (b == 0)
            return { x, 0 };
        return { x, -(a * x + c) / b };
    }
};

template<typename T>
struct Circle {
    Point<T> center;
    T radius = 0;

    Circle() = default;
    Circle(Point<T> _center, T _radius) : center(_center), radius(_radius) {}

    inline bool Inside(const Point<T>& point) const noexcept {
        return center.SquaredDistance(point) <= radius * radius;
    }
};

template<typename T>
struct Segment { Point<T> a, b; };

template<typename T>
using Polygon = vector<Point<T>>;

/*          Functions          */
template<typename T>
inline T sgn(const T& a) { return static_cast<T>(0 < a) - (a < 0); }

template<typename T>
long double Distance(const Line<T>& line, const Point<T>& point) {
    return abs(line.GetOrderedDistance(point)) / line.GetGradient().Distance();
}

template<typename T>
Line<T> PerpendicularBisector(const Segment<T>& segment) {
    Point<T> sum = segment.a + segment.b;
    Line line = { segment.a, segment.b };
    return { line.b * 2, -line.a * 2, -(line.b * sum.x - line.a * sum.y) };
}

template<typename T>
Polygon<T> ConvexHull(vector<Point<T>> p) {  // Returns convex hull in clockwise order
    sort(p.begin(), p.end(), [](Point<T> a, Point<T> b) { return (a.x == b.x) ? a.y < b.y : a.x < b.x; });
    int n = p.size();
    if (n < 3)
        return p;
    vector<Point<T>> hull;
    for (int i = 0; i < n; ++i) {
        while (hull.size() >= 2) {
            Point<T> a = hull[hull.size() - 2], b = hull.back(), c = p[i];
            Vector<T> ab = { a, b }, bc = { b, c };
            if (sgn(ab % bc) >= 0)
                hull.pop_back();
            else
                break;
        }
        hull.pb(p[i]);
    }

    hull.pb(p[n - 2]);
    int lim = hull.size();
    for (int i = n - 3; i >= 0; i--) {
        while (hull.size() >= lim) {
            Point<T> a = hull[hull.size() - 2], b = hull.back(), c = p[i];
            Vector<T> ab = { a, b }, bc = { b, c };
            if (sgn(ab % bc) >= 0)
                hull.pop_back();
            else
                break;
        }
        hull.pb(p[i]);
    }
    hull.pop_back();

    return hull;
}

/*          Intersections          */
template<typename T>
bool Intersect(const Line<T>& line1, const Line<T>& line2, Point<T>* result = nullptr) {
    T vector_product = line1.a * line2.b - line1.b * line2.a;
    if (abs(vector_product) < 1e-9)
        return false;

    if (result != nullptr) {
        result->x = (line2.b * line1.c - line2.c * line1.b) / vector_product;
        result->y = (line2.c * line1.a - line2.a * line1.c) / vector_product;
    }
    return true;
}

template<typename T>
inline bool Intersect(const Segment<T>& segment, const Point<T>& point) {
    return sgn((segment.a - point) % (segment.b - point)) == 0
           && sgn((segment.a - point) * (segment.b - point)) <= 0;
}

template<typename T>
inline bool Intersect(const Segment<T>& segment1, const Segment<T>& segment2, Point<T>* result = nullptr) {
    const Point<T>& a = segment1.a, b = segment1.b, c = segment2.a, d = segment2.b;

    const Point<T>* innerPoint = nullptr;
    if (Intersect(segment1, c)) innerPoint = &c;
    if (Intersect(segment1, d)) innerPoint = &d;
    if (Intersect(segment2, a)) innerPoint = &a;
    if (Intersect(segment2, b)) innerPoint = &b;
    if (innerPoint != nullptr) {
        if (result != nullptr) {
            *result = *innerPoint;
        }
        return true;
    }

    Vector<T> ab = { a, b }, bc = { b, c }, bd = { b, d };
    Vector<T> da = { d, a }, db = { d, b }, cd = { c, d };
    if (sgn(ab % bc) != sgn(ab % bd) && sgn(cd % da) != sgn(cd % db)) {
        return Intersect(Line(segment1.a, segment1.b), Line(segment2.a, segment2.b), result);
    } else {
        return false;
    }
}

template<typename T>
inline bool Intersect(const Point<T>& a, const Point<T>& b, const Point<T>& c, const Point<T>& d) {
    return Intersect({ a, b }, Segment{ c, d });
}

template<typename T>
bool Intersect(const Polygon<T>& polygon, const Point<T>& point) {
    int intersections = 0;
    for (size_t i = 0; i < polygon.size(); i++) {
        Point<T> a = polygon[i], b = polygon[(i + 1) % polygon.size()];
        if (a.y > b.y)
            swap(a, b);
        if (Intersect(Segment{ a, b }, point))
            return true;
        else if (a.y == point.y)
            continue;
        else if (Intersect(a, b, point, { 1000000000, point.y }))
            ++intersections;
    }
    return intersections % 2 != 0;
}

template<typename T>
bool Intersect(const Polygon<T>& polygon1, const Polygon<T>& polygon2) {
    for (size_t i = 0; i < polygon1.size(); ++i)
        if (Intersect(polygon2, polygon1[i]))
            return true;

    for (size_t i = 0; i < polygon2.size(); ++i)
        if (Intersect(polygon1, polygon2[i]))
            return true;

    for (size_t i = 0; i < polygon1.size(); ++i)
        for (size_t j = 0; j < polygon2.size(); ++j)
            if (Intersect(polygon1[i], polygon1[(i + 1) % polygon1.size()],
                          polygon2[j], polygon2[(j + 1) % polygon2.size()]))
                return true;

    return false;
}

template<typename T>
bool Intersect(const Segment<T>& segment, const Polygon<T>& polygon) {
    for (size_t i = 0; i < polygon.size(); ++i)
        if (Intersect(polygon[i], polygon[(i + 1) % polygon.size()],
                      segment.a, segment.b))
            return true;

    return Intersect(polygon, segment.a) || Intersect(polygon, segment.b);
}
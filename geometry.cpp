/*          Classes          */

const static long double PI = acosl(-1.0l);

template<typename T>
struct Vector {
    T x = 0, y = 0;

    Vector() = default;
    [[maybe_unused]] Vector(T _x, T _y) : x(_x), y(_y) {}
    [[maybe_unused]] Vector(const Vector& a, const Vector& b) : x(b.x - a.x), y(b.y - a.y) {}

    Vector operator+(const Vector& o) const { return { x + o.x, y + o.y }; }
    Vector operator-(const Vector& o) const { return { x - o.x, y - o.y }; }
    Vector operator*(T scalar) const { return { x * scalar, y * scalar }; }
    Vector<long double> operator/(long double scalar) const { return { 1.0l * x / scalar, 1.0l * y / scalar }; }

    /*
     * Dot product:
     * if a * b > 0, then angle between them is < 90 degrees
     * if a * b = 0, then a is perpendicular to b
     * if a * b < 0, then angle between them is > 90 degrees
     */
    T operator*(const Vector& o) const { return x * o.x + y * o.y; }  // Dot product
    T operator,(const Vector& o) const { return operator*(o); }

    /*
     * Vector product:
     * if a % b > 0, then b is located on the left of a
     * if a % b = 0, then a and b are parallel
     * if a % b < 0, then b is located on the right of a
     */
    T operator%(const Vector& o) const { return x * o.y - y * o.x; }  // Vector product

    constexpr inline Vector<long double> ToLongDouble() const noexcept {
        return {static_cast<long double>(x), static_cast<long double>(y)};
    }

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

    [[maybe_unused]] inline long double PolarAngleBetween(const Vector& vector) const noexcept {
        long double difference = max(vector.PolarAngle(), PolarAngle()) - min(vector.PolarAngle(), PolarAngle());
        if (difference > PI) {
            return 2.0l * PI - difference;
        } else {
            return difference;
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
using Point = Vector<T>;

template<typename T>
struct Line {
    T a, b, c;

    Line() = default;
    [[maybe_unused]] Line(T A, T B, T C) : a(A), b(B), c(C) {}

    Line(const Vector<T>& gradient, T c) : a(-gradient.y), b(gradient.x), c(c) {}

    Line(const Point<T>& A, const Point<T>& B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = -(a * A.x + b * A.y);
    }

    Vector<T> GetGradient() const { return { b, -a }; }

    long double GetGradientLength() const { return GetGradient().Distance(); }

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

    [[maybe_unused]] constexpr Point<long double> Reflect(const Point<T>& p) {
        Line n{ GetNormal(p) };
        Vector<long double> direction = n.GetGradient().ToLongDouble() * (static_cast<long double>(GetOrderedDistance(p)) / GetGradientLength());
        Point<long double> result = p + direction * 2;
        assert(GetOrderedDistance(p) + GetOrderedDistance(result) < 1e-6);
        return result;
    }

    // If b = 0, then y = offset and x is derived; If b != 0 then x = offset and y is derived;
    constexpr inline Point<long double> GetPointByOffset(T offset) const {
        if (b == 0) {
            // ax + by + c = 0 => x = -(by + c) / a
            return {-static_cast<long double>(b * offset + c) / a, static_cast<long double>(offset)};
        } else {
            // ax + by + c = 0 => y = -(ax + c) / b
            return {static_cast<long double>(offset), -static_cast<long double>(a * offset + c) / b};
        }
    }

    [[maybe_unused]] constexpr inline Line<long double> Offset(T r) const {
        Vector normal = {a, b};
        Vector<long double> offset = normal / normal.Distance() * r;
        return Line<long double>(GetPointByOffset(0) + offset, GetPointByOffset(1) + offset);
    }
};

template<typename T>
struct [[maybe_unused]] Circle {
    Point<T> center;
    T radius = 0;

    Circle() = default;
    [[maybe_unused]] Circle(Point<T> _center, T _radius) : center(_center), radius(_radius) {}

    [[maybe_unused]] inline bool Inside(const Point<T>& point) const noexcept {
        return center.SquaredDistance(point) <= radius * radius;
    }
};

template<typename T>
struct Segment { Point<T> a, b; };

template<typename T>
struct Ray { Point<T> a, b; };

template<typename T>
using Polygon = vector<Point<T>>;

template<typename T>
istream& operator>>(istream& is, Polygon<T>& pol) {
    size_t n;
    is >> n;
    pol.resize(n);
    for (int i = 0; i < n; ++i) {
        is >> pol[i];
    }
    return is;
}

/*          Functions          */
template<typename T>
inline T sgn(const T& a) { return static_cast<T>(0 < a) - (a < 0); }

/*          Distance           */

template<typename T>
[[maybe_unused]] inline T SquaredDistance(const Vector<T>& a, const Vector<T>& b) {
    return a.SquaredDistance(b);
}

template<typename T>
inline long double Distance(const Point<T>& a, const Point<T>& b) noexcept {
    return a.Distance(b);
}

template<typename T>
inline long double Distance(const Line<T>& line, const Point<T>& point) noexcept {
    return abs(line.GetOrderedDistance(point)) / line.GetGradient().Distance();
}

template<typename T>
inline long double Distance(const Ray<T>& ray, const Point<T>& point) noexcept {
    if ((ray.b - ray.a) * (point - ray.a) < 0) {
        return Distance(ray.a, point);
    }
    return Distance(Line(ray.a, ray.b), point);
}

template<typename T>
inline long double Distance(const Segment<T>& segment, const Point<T>& point) noexcept {
    if ((segment.b - segment.a) * (point - segment.a) < 0) {
        return Distance(segment.a, point);
    }
    if ((segment.a - segment.b) * (point - segment.b) < 0) {
        return Distance(segment.b, point);
    }
    return Distance(Line(segment.a, segment.b), point);
}

template<typename T>
inline long double Distance(const Ray<T>& ray1, const Ray<T>& ray2) noexcept {
    if (Intersect(ray1, ray2)) {
        return 0;
    }
    return min(Distance(ray1, ray2.a), Distance(ray2, ray1.a));
}

template<typename T>
inline long double Distance(const Segment<T>& seg1, const Segment<T>& seg2) noexcept {
    if (Intersect(seg1, seg2)) {
        return 0;
    }
    return min({
        Distance(seg1, seg2.a),
        Distance(seg1, seg2.b),
        Distance(seg2, seg1.a),
        Distance(seg2, seg1.b)
    });
}

template<typename T>
[[maybe_unused]] inline Line<T> PerpendicularBisector(const Segment<T>& segment) noexcept {
    Point<T> sum = segment.a + segment.b;
    Line line = { segment.a, segment.b };
    return { line.b * 2, -line.a * 2, -(line.b * sum.x - line.a * sum.y) };
}

template<typename T>
[[maybe_unused]] inline bool Bisector(const Point<T>& center, const Point<T>& a, const Point<T>& b,
              bool interior, Line<long double>* result)
{
    Line<T> line1(center, a);
    Line<T> line2(center, b);
    if (line1.GetGradient() % line2.GetGradient() == 0) {
        return false;
    }
    if (result != nullptr) {
        long double sign = interior ? 1.0l : -1.0l;
        *result = Line(
                line2.GetGradient() / line2.GetGradientLength() + line1.GetGradient() / line1.GetGradientLength() * sign,
                line2.c / line2.GetGradientLength() + line1.c / line1.GetGradientLength() * sign
        );
    }

    return true;
}

template<typename T>
[[maybe_unused]] Polygon<T> ConvexHull(vector<Point<T>> p) {  // Returns convex hull in clockwise order
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

template<typename T>
[[maybe_unused]] inline long double Area(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    return abs((b - a) % (c - a)) / 2.0l;
}

template<typename T>
[[maybe_unused]] inline long double Area(const Polygon<T>& pol) {
    T result = 0;
    for (size_t i = 0; i < pol.size(); ++i) {
        result += pol[i] % pol[(i + 1) % pol.size()];
    }
    return abs(result) / 2.0l;
}


/*          Intersections          */

template<typename T>
[[maybe_unused]] constexpr inline bool Intersect(const Line<T>& line, const Point<T>& point) {
    return line.GetOrderedDistance(point) == 0;
}

template<typename T>
[[maybe_unused]] constexpr inline bool Intersect(const Ray<T>& ray, const Point<T>& point) {
    return (ray.b - ray.a) % (point - ray.a) == 0 && (ray.b - ray.a) * (point - ray.a) >= 0;
}

template<typename T>
[[maybe_unused]] constexpr inline bool Intersect(const Line<T>& line1, const Line<T>& line2, Point<long double> * const result = nullptr) noexcept {
    long double vector_product = line1.a * line2.b - line1.b * line2.a;

    if (abs(vector_product) < 1e-9) {
        if (abs(line1.c - line2.c) < 1e-9) {
            if (result != nullptr) {
                *result = line1.GetPointByOffset(0);
            }
            return true;
        } else {
            return false;
        }
    }

    if (result != nullptr) {
        result->x = (line2.c * line1.b - line2.b * line1.c) / vector_product;
        result->y = (line2.a * line1.c - line2.c * line1.a) / vector_product;
    }
    return true;
}

template<typename T>
[[maybe_unused]] inline bool Intersect(const Segment<T>& segment, const Point<T>& point) {
    return sgn((segment.a - point) % (segment.b - point)) == 0
        && sgn((segment.a - point) * (segment.b - point)) <= 0;
}

template<typename T>
constexpr inline bool Intersect(const Ray<T>& ray1, const Ray<T>& ray2, Point<long double> * const result = nullptr) noexcept {
    const Point<T>* innerPoint = nullptr;
    if (Intersect(ray1, ray2.a)) innerPoint = &ray2.a;
    if (Intersect(ray2, ray1.a)) innerPoint = &ray1.a;
    if (innerPoint != nullptr) {
        if (result != nullptr) {
            *result = innerPoint->ToLongDouble();
        }
        return true;
    }

    Line l1(ray1.a, ray1.b), l2(ray2.a, ray2.b);
    Point<long double> line_intersect_result;
    if (Intersect(l1, l2, &line_intersect_result)) {
        if ((line_intersect_result - ray1.a.ToLongDouble()) * (ray1.b.ToLongDouble() - ray1.a.ToLongDouble()) >= 0
         && (line_intersect_result - ray2.a.ToLongDouble()) * (ray2.b.ToLongDouble() - ray2.a.ToLongDouble()) >= 0)
        {
            if (result != nullptr) {
                *result = line_intersect_result;
            }
            return true;
        }
    }
    return false;
}

template<typename T>
constexpr inline bool Intersect(const Segment<T>& segment1, const Segment<T>& segment2, Point<long double> * const result = nullptr) noexcept {
    const Point<T>& a = segment1.a, b = segment1.b, c = segment2.a, d = segment2.b;

    const Point<T>* innerPoint = nullptr;
    if (Intersect(segment1, c)) innerPoint = &c;
    if (Intersect(segment1, d)) innerPoint = &d;
    if (Intersect(segment2, a)) innerPoint = &a;
    if (Intersect(segment2, b)) innerPoint = &b;
    if (innerPoint != nullptr) {
        if (result != nullptr) {
            *result = {innerPoint->x, innerPoint->y};
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
constexpr bool Intersect(const Polygon<T>& polygon, const Point<T>& point, Point<T> * const result = nullptr) noexcept {
    int intersections = 0;
    for (size_t i = 0; i < polygon.size(); i++) {
        Point<T> a = polygon[i], b = polygon[(i + 1) % polygon.size()];
        if (a.y > b.y)
            swap(a, b);
        if (Intersect(Segment{ a, b }, point)) {
            if (result != nullptr) {
                *result = point;
            }
            return true;
        }
        else if (a.y == point.y)
            continue;
        else if (Intersect(a, b, point, { 1000000000, point.y }))
            ++intersections;
    }
    if (intersections % 2 != 0) {
        if (result != nullptr) {
            *result = point;
        }
        return true;
    } else {
        return false;
    }
}

template<typename T>
inline bool Intersect(const Polygon<T>& polygon1, const Polygon<T>& polygon2, Point<T> * const result = nullptr) noexcept {
    for (size_t i = 0; i < polygon1.size(); ++i)
        if (Intersect(polygon2, polygon1[i], result))
            return true;

    for (size_t i = 0; i < polygon2.size(); ++i)
        if (Intersect(polygon1, polygon2[i], result))
            return true;

    for (size_t i = 0; i < polygon1.size(); ++i) {
        for (size_t j = 0; j < polygon2.size(); ++j) {
            if (Intersect(Segment(polygon1[i], polygon1[(i + 1) % polygon1.size()]),
                          Segment(polygon2[j], polygon2[(j + 1) % polygon2.size()]), result))
            {
                return true;
            }
        }
    }

    return false;
}

template<typename T>
inline bool Intersect(const Segment<T>& segment, const Polygon<T>& polygon, Point<T> * const result = nullptr) noexcept {
    for (size_t i = 0; i < polygon.size(); ++i) {
        if (Intersect(Segment(polygon[i], polygon[(i + 1) % polygon.size()]), segment, result)) {
            return true;
        }
    }
    return Intersect(polygon, segment.a, result) || Intersect(polygon, segment.b, result);
}
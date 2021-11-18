using Double = long double;

template<typename T>
struct Vector {
    T x = 0, y = 0, z = 0;

    Vector() = default;
    Vector(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}

    Vector operator+(const Vector& other) const {
        return { x + other.x, y + other.y, z + other.z };
    }

    Vector operator-(const Vector& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }

    Vector& operator+=(const Vector& other) {
        return *this = *this + other;
    }

    T operator,(const Vector& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    T SquaredLength() const { return x * x + y * y + z * z; }
    Double Length() const { return sqrt(SquaredLength()); }

    friend istream& operator>>(istream& is, Vector& vector) {
        return is >> vector.x >> vector.y >> vector.z;
    }
};
template<typename T>
using Point = Vector<T>;

template<typename T>
struct Plane {  // Ax + By + Cz + D = 0
    T A, B, C, D;

    Point<T> v0;

    Plane(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3) {
        v0 = p1;
        Vector<T> v = p2 - p1, w = p3 - p1;
        /*
        | x - p1.x   v.x   w.x |
        | y - p1.y   v.y   w.y |                    | v.y w.y |              | v.x w.x |              | v.x w.x |
        | z - p1.z   v.z   2.z | = 0 <=> (x - p1.x) | v.z w.z | - (y - p1.y) | v.z w.z | + (z - p1.z) | v.y w.y | = 0
        */
        T det1 = v.y * w.z - w.y * v.z, det2 = v.x * w.z - v.z * w.x, det3 = v.x * w.y - v.y * w.x;
        A = det1; B = -det2; C = det3;
        D = -(A * p1.x + B * p1.y + C * p1.z);
    }

    Vector<T> GetNormal() const { return { A, B, C }; }
};

template<typename T>
struct Face : public vector<Point<T>> {
    Plane<T> GetPlane() const {
        return { operator[](0), operator[](1), operator[](2) };
    }

    const Point<T> operator[](size_t ind) const { return vector<Point<T>>::operator[](ind); }
    Point<T> operator[](size_t ind) { return vector<Point<T>>::operator[](ind); }
};

template<typename T>
using Polyhedron = vector<Point<T>>;

template<typename T>
Double Distance(const Plane<T>& plane, const Point<T>& point) {
    return static_cast<Double>(abs((point - plane.v0, plane.GetNormal()))) / plane.GetNormal().Length();
}
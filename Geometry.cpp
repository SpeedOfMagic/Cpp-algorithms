class pt {
    public:
        int x;
        int y;

        pt() {}
        pt(int _x, int _y) : x(_x), y(_y) {}
        pt(pt p1, pt p2) {
            this -> x = p2.x - p1.x;
            this -> y = p2.y - p1.y;
        }

        pt operator-() { return pt(-this -> x, -this -> y); }
        pt operator+(pt b) { return pt(this -> x + b.x, this -> y + b.y); }
        pt operator-(pt b) { return *this + (-b);}
        pt operator*(int b) { return pt(this -> x * b, this -> y * b); }
        pt operator/ (int b) { return pt(this -> x / b, this -> y / b); }

        int operator*(pt b) {return this -> x * b.x + this -> y * b.y;}  // Scalar multiplication
        int operator%(pt b) {return this -> x * b.y - this -> y * b.x;}  // Vector multiplication

        bool operator==(pt b) { return this -> x == b.x && this -> y == b.y; }
        bool operator!=(pt b) { return !((*this) == b); }

        bool collinear(pt b) {return (*this) % b == 0;}
        bool perpendicular(pt b) {return (*this) * b == 0;}
        bool opposite(pt b) {return this -> collinear(b) && (*this) * b < 0;}
        bool codirect(pt b) {return this -> collinear(b) && !this -> opposite(b);}

        double length() {return sqrt(sqLength());}
        int sqLength() {return this -> x * this -> x + this -> y * this -> y;}
        double polar() {return atan2(this -> y, this -> x);}
};

struct line : public pt {
    int a, b, c; // a * x + b * y + c = 0

    line(int _a, int _b, int _c = 0) : a(_a), b(_b), c(_c) {
        this -> x = -b;
        this -> y = a;
    }

    line(pt v, int _c = 0) : a(v.y), b(-v.x), c(_c) {
        this -> x = v.x;
        this -> y = v.y;
    }

    bool operator==(line other) { return (this -> a == other.a) && (this -> b == other.b) && (this -> c == other.c); }
};

struct seg {
    pt p1;
    pt p2;

    seg(pt _p1, pt _p2) : p1(_p1), p2(_p2) {}
};

bool intersects(line l1, line l2) { return (l1 == l2 || !l1.collinear(l2)); }
bool intersects(line l, pt p) { return l.a * p.x + l.b * p.y + l.c == 0; }
///bool intersects(seg s, pt p)
///bool intersects(seg s1, seg s2)

pt intersectionPoint(line l1, line l2) {
    assert(intersects(l1, l2) && !(l1 == l2));
    int x = (l1.b * l2.c - l1.c * l2.b) / (l1.a * l2.b - l1.b * l2.a);
    int y = -(l2.a * x + l2.c) / l2.b;
    return pt(x, y);
    /**
    l1.a * x + l1.b * y + l1.c = 0
    l2.a * x + l2.b * y + l2.c = 0

    y = -(l2.a * x + l2.c) / l2.b

    l1.a * x + l1.b * -(l2.a * x + l2.c) / l2.b + l1.c = 0
    l1.a * x - l1.b * (l2.a * x + l2.c) / l2.b + l1.c = 0
    l1.a * x - l1.b * l2.a * x / l2.b - l1.b * l2.c / l2.b + l1.c = 0
    l1.a * x - l1.b * l2.a / l2.b * x - l1.b * l2.c / l2.b + l1.c = 0
    l1.a * l2.b * x - l1.b * l2.a * x - l1.b * l2.c + l1.c * l2.b = 0
    (l1.a * l2.b - l1.b * l2.a) * x - l1.b * l2.c + l1.c * l2.b = 0
    x = (l1.b * l2.c - l1.c * l2.b) / (l1.a * l2.b - l1.b * l2.a)
    **/
}

pt move(pt cur, pt direction) { return cur + direction; }
line move(line cur, pt direction) { return line(cur, cur.c + pt(cur.x, cur.y) * direction); }

pt reflect(pt cur, pt center = pt(0, 0)) { return move(-(cur - center), center); }

pt perp(line axis) { return pt(-axis.y, axis.x); }

pt perp(pt cur, line axis) {
    line d = line(perp(axis));
    d.c = -(d.b * cur.y + d.a * cur.x);
    return pt(cur, intersectionPoint(d, axis));
}

pt reflect(pt cur, line axis) { return move(cur, perp(cur, axis) * 2);}

///double dist(pt p, line l)
///double dist(pt p, seg s)
///double dist(line l1, line l2)
///double dist(seg s1, seg s2)
///pt<double> rotate(pt cur, double angle)
typedef long long T;
struct pt {
	T x, y;
	
	pt() {}
	pt(T _x, T _y) : x(_x), y(_y) {}
	pt(pt a, pt b) : x(b.x - a.x), y(b.y - a.y) {}
	pt operator-(pt o) const { return { x - o.x, y - o.y }; }
	
	T sqDist(pt o) { return (o.x - x) * (o.x - x) + (o.y - y) * (o.y - y); }
	T operator*(pt o) const { return x * o.x + y * o.y; }
	T operator%(pt o) const { return x * o.y - y * o.x; }
	
	long double dist(pt o) {
		return sqrt(sqDist(o));
	}		
};

struct line {
	T a, b, c;

	line(T A, T B, T C) : a(A), b(B), c(C) {}

	line(pt A, pt B) {
		a = A.y - B.y;
		b = B.x - A.x;
		c = -(a * A.x + b * A.y);
	}

	bool intersect(line l, pt& ans) {
		if (abs((l.a * b - l.b * a)) < EPS)
			return false;
 
		ans.x = (l.b * c - l.c * b) / (-l.b * a + l.a * b);
		ans.y = (l.c * a - l.a * c) / (-l.b * a + l.a * b);
		return true;
	}
	
	T ord(pt p) { return p.x * a + p.b * y + c; }
};

line perpBisector(pt a, pt b) {
	pt mid2 = {a.x + b.x, a.y + b.y};
	line l = {a, b};
	return {l.b * 2, -l.a * 2, -(l.b * mid2.x - l.a * mid2.y)};
}

struct circle {
	pt o;
	T r;
	
	circle(pt O, T R) : o(O), r(R) {}
	
	circle(pt a, pt b, pt c) {
		line l1 = perpBisector(a, b), l2 = perpBisector(b, c);
		assert(l1.intersect(l2, o));
		r = o.dist(a);
	}
};

int sgn(T a) { return (0 < a) - (a < 0); }

bool segPoint(pt a, pt b, pt p) { return sgn((a - p) % (b - p)) == 0 && sgn((a - p) * (b - p)) <= 0; }

bool segSeg(pt a, pt b, pt c, pt d) {
	if (belongs(a, b, c) || belongs(a, b, d) || belongs(c, d, a) || belongs(c, d, b))
		return 1;
	pt ab = { a, b }, bc = { b, c }, bd = { b, d }, da = { d, a }, db = { d, b }, cd = { c, d };
	return (sgn(ab % bc) != sgn(ab % bd) && sgn(cd % da) != sgn(cd % db));
}

bool in(vector<pt> pol, pt p) { //uses belongs, segSeg
	int n = pol.size();
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		pt a = pol[i], b = pol[(i + 1) % n];
		if (a.y > b.y)
			swap(a, b);
		if (belongs(a, b, p))
			return true;
		else if (a.y == p.y)
			continue;
		else if (segSeg(a, b, p, { 1000000000, p.y }))
			cnt++;
	}
	return cnt % 2;
}

bool polSeg(vector<pt>& pol, pt a, pt b) {
	if (in(pol, a) || in(pol, b))
		return 1;
 
	rep(i, 0, sz(pol)) {
		pt c = pol[i], d = pol[(i + 1) % sz(pol)];
		if (segSeg(a, b, c, d))
			return 1;
	}
	return 0;
}

vector<pt> convexHull(vector<pt> p) { //makes hull in clockwise order
	sort(p.begin(), p.end(), [](pt a, pt b) { return (a.x == b.x) ? a.y < b.y : a.x < b.x; });
	int n = p.size();
	if (n < 3)
		return p;
	vector<pt> hull;
	rep(i, 0, n) {
		while (sz(hull) >= 2) {
			pt a = hull[sz(hull) - 2], b = hull.back(), c = p[i];
			pt ab = { a, b }, bc = { b, c };
			if (sgn(ab % bc) >= 0)
				hull.pop_back();
			else
				break;
		}
		hull.pb(p[i]);
	}

	hull.pb(p[n - 2]);
	int lim = sz(hull);
	for (int i = n - 3; i >= 0; i--) {
		while (sz(hull) >= lim) {
			pt a = hull[sz(hull) - 2], b = hull.back(), c = p[i];
			pt ab = { a, b }, bc = { b, c };
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
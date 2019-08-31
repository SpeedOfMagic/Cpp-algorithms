mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
struct treap {
    treap *l = nullptr, *r = nullptr;
    int x, y, siz = 1;
    int lazy = 0;
	int val;
    treap(int xx) : x(xx), y(rng()) {}
    void upd() {
        pushdown();
        val = x;
        if (l != nullptr) { l -> pushdown(); val = max(val, l -> val); }
        if (r != nullptr) { r -> pushdown(); val = max(val, r -> val); }
        siz = ((l == nullptr) ? 0 : l -> siz) + ((r == nullptr) ? 0 : r -> siz) + 1;

    }

    void pushdown() {
        val += lazy;
        x += lazy;
        if (l != nullptr) l -> lazy += lazy;
        if (r != nullptr) r -> lazy += lazy;
        lazy = 0;
    }
};
 
int siz(treap* a) { return (a == nullptr) ? 0 : a -> siz; }
int val(treap* t) { if (t == nullptr) return 0; t -> pushdown(); return t -> val; }
 
treap* merge(treap* t1, treap* t2) {
    if (t1 == nullptr)
        return t2;
    if (t2 == nullptr)
        return t1;
    t1 -> pushdown();
    t2 -> pushdown();
    if (t1 -> y > t2 -> y) {
        t1 -> r = merge(t1 -> r, t2);
        t1 -> upd();
        return t1;
    } else {
        t2 -> l = merge(t1, t2 -> l);
        t2 -> upd();
        return t2;
    }
}
 
pair<treap*, treap*> split(treap* t, int k) {
    if (t == nullptr)
        return {nullptr, nullptr};
    t -> pushdown();
 
    if (siz(t -> l) >= k) {
        pair<treap*, treap*> res = split(t -> l, k);
        t -> l = res.sc;
        t -> upd();
        return {res.fs, t};
    } else {
        pair<treap*, treap*> res = split(t -> r, k - siz(t -> l) - 1);
        t -> r = res.fs;
        t -> upd();
        return {t, res.sc};
    }
}
 
treap *root = nullptr;
 
inline treap* addAll(treap *t, int a) {
    if (t != nullptr)
        t -> lazy += a;
	return t;
}

inline int query(int amount) {
    int ans = 0;
    treap *cur = root;
    while (cur != nullptr) {
        if (siz(cur -> l) + 1 <= amount) {
            ans = max(ans, max((cur -> l == nullptr) ? 0 : cur -> l -> val, cur -> x));
			amount -= siz(cur -> l) + 1;
            cur = cur -> r;
        } else
            cur = cur -> l;
    }
    return ans;
}
 
inline treap* ins(treap* a, treap *t) {
	a -> upd();
    treap *cur = t;
    int amount = 0;
    while (cur != nullptr) {
        cur -> pushdown();
        if (cur -> x < a -> x) {
            amount += siz(cur -> l) + 1;
            cur = cur -> r;
        } else
            cur = cur -> l;
    }
 
    pair<treap*, treap*> p = split(t, amount);
    t = merge(merge(p.fs, a), p.sc);
	return t;
}
 
inline treap* rem(int a, treap *t) {
    treap *cur = t;
    int amount = 0;
    while (cur != nullptr) {
        if (cur -> x < a) {
            amount += siz(cur -> l) + 1;
            cur = cur -> r;
        } else if (cur -> x == a) {
			amount += siz(cur -> l);
			break;
		} else
            cur = cur -> l;
    }

    pair<treap*, treap*> p = split(root, amount);
	pair<treap*, treap*> d = split(p.sc, 1);

    t = merge(p.fs, d.sc);
	return t;
}

treap* getLast(treap *t) {
	treap *ans = t;
	for (; t != nullptr; t = t -> r) {
		t -> pushdown();
		ans = t;
	}
	return ans;
}

treap* getFirst(treap *t) {
	treap *ans = t;
	for (; t != nullptr; t = t -> l) {
		t -> pushdown();
		ans = t;
	}
	return ans;
}
 
void prnt(treap* cur) {
    if (cur == nullptr)
        return;
    cur -> pushdown();
    prnt(cur -> l);
    print(cur -> x);
    prnt(cur -> r);
}
const int N = 1 << 17;
const int D = 18;
const int Q = 200001;
int val[Q][D];
int Left[Q][D];
int Right[Q][D];

void init() {
	rep(i, 0, D) {
		val[0][i] = 0;
		Left[0][i] = 0;
		Right[0][i] = 0;
	}
}

int query(int l, int r, int curVersion, int d = 0, int ll = 1, int rr = N) {
	if (l > r)
		return 0;
	if (l == ll && r == rr)
		return val[curVersion][d];
	int mid = (ll + rr) >> 1;
	return query(l, min(r, mid), Left[curVersion][d], d + 1, ll, mid) +
		   query(max(l, mid + 1), r, Right[curVersion][d], d + 1, mid + 1, rr);
}

int versionCount = 1;
void update(int num, int v, int prevVersion) {
	int parallel = prevVersion;

	int cur = versionCount;
	int ll = 1, rr = N;
	for (int d = 0; ll != rr; d++) {
		int mid = (ll + rr) >> 1;
		if (num > mid) {
			ll = mid + 1;
			Left[cur][d] = Left[parallel][d];
			Right[cur][d] = cur;
			parallel = Right[parallel][d];
		} else {
			rr = mid;
			Left[cur][d] = cur;
			Right[cur][d] = Right[parallel][d];
			parallel = Left[parallel][d];
		}
	}

	val[cur][D - 1] = v;
	for (int i = D - 2; i >= 0; i--)
		val[cur][i] = val[Left[cur][i]][i + 1] + val[Right[cur][i]][i + 1];

	versionCount++;
}

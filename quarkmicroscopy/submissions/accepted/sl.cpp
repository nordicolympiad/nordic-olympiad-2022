#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto& a : x)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll NONE = -100;
const ll SINGLE = -101;

const ll MAXV = 1'000'000'000'000'000'000LL;

int T;

map<ll, pair<ll, int>> mem;

pair<ll, int> query(ll x, bool rev = false) {
	if (rev) x = MAXV+1 - x;
	x = max(x, 1LL);
	x = min(x, MAXV);
	pair<ll, int>& out = mem[x];
	if (out.second) return out;
	cout << "? " << x << endl;
	int count;
	cin >> x >> count;
	return out = {x, count};
}

ll findA(ll b, bool rev = false) {
	ll x, y;
	int count;
	tie(x, count) = query(b, rev);
	if (count == 2) return b - x;
	tie(y, count) = query(b - 1, rev);
	if (count == 2) return b - 1 - y;
	if (y == x - 1) return b - x;
	if (y == x && x == 1) return b - x;
	if (y == x) return b - x - 1;
	assert(y == x + 1);
	ll c = b + x;

	ll lo = b, hi = 0;
	ll hiAns = -1;
	while (lo - 1 > hi) {
		ll mid = (lo + hi) / 2;
		tie(x, count) = query(mid, rev);
		if (mid + x == c && count == 2) return mid - x;
		if (mid + x == c) lo = mid;
		else {
			hi = mid;
			hiAns = x;
		}
	}
	// lo -> c, lo-0.5 -> c & a, hi -> a
	return hi - hiAns;
}

ll findNext(ll a, ll lo, ll hi) {
	ll x, hiAns = -1;
	int count;
	while (lo + 1 < hi) {
		ll mid = (lo + hi) / 2;
		tie(x, count) = query(mid);
		if (mid - x == a && count == 2) {
			return mid + x;
		}
		if (mid - x == a) lo = mid;
		else {
			hi = mid;
			hiAns = x;
		}
	}
	assert(hiAns != -1);
	// lo -> a, lo+0.5 -> a & c, hi -> c
	return hi + hiAns;
}

vector<ll> ev;

ll findOne(ll a, ll z) {
	assert(a < z);
	if (z - a == 1) return NONE;
	if (z - a == 2) return SINGLE;

	ll mid = (a + z) / 2, x, y;
	int count;
	tie(x, count) = query(mid);

	if (x > mid - a) {
		assert((z - a) % 2);
		return NONE;
	}

#define RET(q) do { assert(a < q); assert(q < z); return q; } while (0)

	if (count == 2) {
		ll s = mid - x, t = mid + x;
		if (s != a) RET(s);
		if (t != z) RET(t);
		return SINGLE;
	}

	// guaranteed non-empty at this point

	if (x == 1) RET(mid);

	if (x == mid - a) {
		assert((z - a) % 2);
		return SINGLE;
	}

	// guaranteed at least two points

	ll mid2 = mid + 1;
	tie(y, count) = query(mid2);

	if (count == 2) RET(mid2 - y);

	if (y == x + 1) RET(mid - x);
	if (y == x - 1) RET(mid + x);

	assert(x == y);

	tie(y, count) = query(mid + x);
	if (count == 2) RET(mid + x - y);

	tie(y, count) = query(mid - 1);

	if (y == x - 1) RET(mid - x);
	else RET(mid - x + 1);
#undef RET
}

void rec(ll a, ll z) {
	ll mid = findOne(a, z);
	if (mid == SINGLE) {
		ev.push_back(SINGLE);
	}
	else if (mid != NONE) {
		assert(a < mid);
		assert(mid < z);
		rec(a, mid);
		ev.push_back(mid);
		rec(mid, z);
	}
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N;
	cin >> N >> T;
	ll x;
	int count;

	tie(x, count) = query(1);
	ll b = x + 1;
	ll a = findA(b);
	assert(a < b);

	tie(x, count) = query(1, true);
	ll b2 = x + 1;
	ll a2 = findA(b2, true);
	assert(a2 < b2);

	ll z = MAXV+1 - a2;

	ev.push_back(a);
	rec(a, z);
	ev.push_back(z);

	vector<ll> points;
	rep(it,0,sz(ev)) {
		ll p = ev[it];
		if (p != SINGLE) points.push_back(p);
		else {
			ll b = ev[it - 1];
			ll c = ev[it + 1];
			assert(b != SINGLE);
			assert(c != SINGLE);
			tie(x, count) = query(b);
			if (b + x >= c) continue;
			if (count == 2 || sz(points) == 1 || points[sz(points) - 2] < b - x) {
				points.push_back(b + x);
				continue;
			}
			ll a = points[sz(points) - 2];
			assert(a == b - x);
			if (c - 1 <= b + x) continue;
			assert(c - b >= 3);

			ll y;
			tie(y, count) = query(c);
			if (c - y <= b + x) continue;
			if (count == 2) {
				points.push_back(c - y);
				continue;
			}

			// check c's closest
			ll z;
			tie(z, count) = query(c - 1);
			if (z == 1) {
				points.push_back(c - 1 - (count == 2));
				continue;
			}
			if (z == y - 1) {
				points.push_back(c - y);
				continue;
			}

			ll q = findNext(a, b, c);
			assert(b < q);
			assert(q <= c);
			if (q != c) points.push_back(q);
		}
	}

	assert(sz(points) == N);
	cout << "! ";
	rep(i,0,sz(points)) cout << points[i] << ' ';
	cout << endl;
}

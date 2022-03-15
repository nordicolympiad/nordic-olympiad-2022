// Q ~ 54 * N => r = 0.6
#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto& a : x)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int T;
const ll MAXV = 1'000'000'000'000'000'000LL;

pair<ll, int> query(ll x) {
	x = max(x, 1LL);
	x = min(x, MAXV);
	cout << "? " << x << endl;
	int count;
	cin >> x >> count;
	return {x, count};
}

ll findA(ll b) {
	ll x, y;
	int count;
	tie(x, count) = query(b);
	if (count == 2) return b - x;
	tie(y, count) = query(b - 1);
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
		tie(x, count) = query(mid);
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
	vector<ll> found = {a, b};

	ll avgDist = MAXV / N;

	rep(it,0,N-2) {
		ll a = found[found.size() - 2];
		ll b = found[found.size() - 1];
		tie(x, count) = query(b);
		if (count == 2) {
			found.push_back(b + x);
			continue;
		}
		if (b - x != a) {
			found.push_back(b + x);
			continue;
		}
		bool linear = true;
		ll lo = b, hi = MAXV + 1;
		ll hiAns = -1;
		while (lo + 1 < hi) {
			ll mid = linear ? min(lo + avgDist, MAXV) : (lo + hi) / 2;
			tie(x, count) = query(mid);
			if (mid - x == a && count == 2) {
				found.push_back(mid + x);
				goto next;
			}
			if (mid - x == a) lo = mid;
			else {
				hi = mid;
				hiAns = x;
				linear = false;
			}
		}
		// lo -> a, lo+0.5 -> a & c, hi -> c
		found.push_back(hi + hiAns);
next:;
	}

	cout << "! ";
	rep(i,0,N) cout << found[i] << ' ';
	cout << endl;
}

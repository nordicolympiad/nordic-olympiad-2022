#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define trav(a, x) for (auto& a : x)
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int Q;
const ll MAXV = 1'000'000'000'000'000'000LL;

pair<ll, int> query(ll x) {
	x = max(x, 1LL);
	x = min(x, MAXV);
	cout << "? " << x << endl;
	int count;
	cin >> x >> count;
	return {x, count};
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N, Q;
	cin >> N >> Q;
	ll x;
	int count;
	tie(x, count) = query(1);
	vector<ll> found = {1, 1 + x};
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
		ll lo = b, hi = MAXV + 1;
		ll hiAns = -1;
		while (lo + 1 < hi) {
			ll mid = (lo + hi) / 2;
			tie(x, count) = query(mid);
			if (mid - x == a && count == 2) {
				found.push_back(mid + x);
				goto next;
			}
			if (mid - x == a) lo = mid;
			else {
				hi = mid;
				hiAns = x;
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

#include "validator.h"

using ll = long long;

const ll MINV = 1;
const ll MAXV = 1'000'000'000'000'000'000;

void run() {
	int n = Int(3, 100);
	Space();
	int t = Arg("t");
	Int(t, t);
	if (t == 0) {
		Space();
		t = Int(1, 3);
	}
	Endl();

	vector<ll> v = SpacedInts(n, MINV, MAXV);
	assert(is_sorted(v.begin(), v.end()));
	assert(unique(v.begin(), v.end()) == v.end());
	if (t == 1) {
		assert(v[0] == 1);
	}
	if (t == 2) {
		for (auto& x : v) assert(x % 2 == 0);
	}
}

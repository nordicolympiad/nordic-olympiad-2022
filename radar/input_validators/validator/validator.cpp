#include "validator.h"

using ll = long long;

const ll MIN_GUESS = 1;
const ll MAX_GUESS = 1'000'000'000'000'000'000;

void run() {
	int n = Arg("n", 100), nq = Arg("nq");
	if (n == -1) n = Int(2, 100);
	else Int(n, n);
	Space();
	int q = nq * n;
	if (nq == -1) q = Int(1, 1000);
	else Int(q, q);
	Space();
	Int(0, 100);
	Endl();
	vector<ll> v = SpacedInts(n, MIN_GUESS, MAX_GUESS);
	assert(is_sorted(v.begin(), v.end()));
	assert(unique(v.begin(), v.end()) == v.end());
}

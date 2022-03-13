#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

const ll MIN_GUESS = 1;
const ll MAX_GUESS = 1'000'000'000'000'000'000;

int main(int argc, char **argv) {
	init_io(argc, argv);

	int N, Q;
	judge_in >> N >> Q;
	assert(judge_in);
	assert(N >= 2);

	vector<ll> points(N);
	for (auto& v : points) judge_in >> v;
	assert(judge_in);
	assert(is_sorted(all(points)));
	assert(unique(all(points)) == points.end());

	cout << N << ' ' << Q << endl;

	string que;
	int queries = 0;
	for (;;) {
		cin >> que;
		if (!cin) wrong_answer("eof");
		if (que == "?") {
			ll x;
			cin >> x;
			if (!cin) wrong_answer("eof2");
			if (x < MIN_GUESS || x > MAX_GUESS) wrong_answer("bad x: %lld", x);
			++queries;
			if (queries > Q) wrong_answer("too many queries");
			int ind = (int)(lower_bound(all(points), x) - points.begin());
			vector<ll> cands;
			rep(i,ind-2,ind+2) {
				if (i >= 0 && i < N) cands.push_back(abs(points[i] - x));
			}
			sort(all(cands));
			ll r = cands[1];
			bool both = (cands[0] == r || (sz(cands) >= 3 && cands[2] == r));
			cout << r << ' ' << (both ? 2 : 1) << endl;
		}
		else if (que == "!") {
			vector<ll> guess(N);
			for (auto& v : guess) cin >> v;
			if (!cin) wrong_answer("eof3");
			if (cin >> que) wrong_answer("expected eof");
			sort(all(guess));
			rep(i,0,N) if (guess[i] != points[i]) {
				wrong_answer(
					"guessed wrong, first diff at index %d (guessed %lld, expected %lld)",
					i, guess[i], points[i]
				);
			}
			break;
		}
		else {
			wrong_answer("bad query type: %s", que.c_str());
		}
	}

	judge_message("%d/%d queries", queries, Q);
	accept();
}

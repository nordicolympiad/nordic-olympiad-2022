#include "validator.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(i, a) for(auto& i : a)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void run() {
  int maxn = Arg("maxn", 100);
  int maxm = Arg("maxm", maxn * (maxn - 1) / 2);

  int n = Int(1,maxn);
  Space();
  int m = Int(0,min(maxm, n * (n - 1) / 2));
  Endl();

  set<pii> s;
  rep(i,0,m) {
    int a = Int(1,n); Space();
    int b = Int(1,n); Endl();
    if(s.count(pii(a,b))) die_line("duplicate edge");
    if(a == b) die_line("self_loop");
    s.emplace(a,b);
    s.emplace(b,a);
  }
  Eof();
}


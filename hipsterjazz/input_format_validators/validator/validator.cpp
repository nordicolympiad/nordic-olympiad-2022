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
  int maxn = Arg("maxn", 200);
  int maxm = Arg("maxm", maxn * (maxn - 1) / 2);
  int bipartite = Arg("bipartite", 0);
  int maxdeg = Arg("maxdeg", maxn);

  int n = Int(1,maxn);
  Space();
  int m = Int(0,min(maxm, n * (n - 1) / 2));
  Endl();

  set<pii> s;
  vector<vi> G(n);
  rep(i,0,m) {
    int a = Int(1,n); Space();
    int b = Int(1,n); Endl();
    --a; --b;
    if(s.count(pii(a,b))) die_line("duplicate edge");
    if(a == b) die_line("self_loop");
    s.emplace(a,b);
    s.emplace(b,a);
    G[a].push_back(b);
    G[b].push_back(a);
  }
  trav(it, G) if (sz(it) > maxdeg) die_line("wrong maxdeg");
  if (bipartite) {
    vector<int> seen(n);
    function<void(int)> dfs = [&](int at) {
      if (seen[at]) return;
      trav(it, G[at]) {
        if (!seen[it]) {
          seen[it] = 3 - seen[at];
          dfs(it);
        } else {
          if (seen[at] + seen[it] != 3) die_line("not bipartite");
        }
      }
    };
    rep(i,0,n) {
      if (seen[i]) continue;
      seen[i] = 1;
      dfs(i);
    }
  }
  Eof();
}


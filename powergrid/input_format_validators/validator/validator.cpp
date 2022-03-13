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
  int maxn = Arg("maxn", 1000);
  int maxm = Arg("maxm", 1000);
  int maxc = Arg("maxc", 1000);

  bool samec = Arg("samec", 0);
  bool diffc = Arg("diffc", 0);

  int n = Int(1,maxn);
  Space();
  int m = Int(1,maxm);
  Endl();

  set<int> S;
  for(int c1 = 0; c1 < n; c1++){
    vi row = SpacedInts(m, 0, maxc);
    for(int c2 = 0; c2 < m; c2++){
      S.insert(row[c2]);
    }
  }

  if(samec)assert(sz(S) == 1);
  if(diffc)assert(sz(S) == n*m);
  Eof();
}


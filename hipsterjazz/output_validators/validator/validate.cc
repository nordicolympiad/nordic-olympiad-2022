#include "validate.h"

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define debug(...) //ignore
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double ld;

int main(int argc, char **argv) {
  init_io(argc, argv);

  int n, m;
  judge_in >> n >> m;

  vector<pii> edges;
  vector<vi> G(n);
  rep(i,0,m) {
    int a, b;
    judge_in >> a >> b;
    --a; --b;
    G[a].push_back(b);
    G[b].push_back(a);
  }

  string ans;
  if (!(author_out >> ans)) {
    wrong_answer("Received no output");
  }
  for (char& c : ans) if (c != 'P' && c != 'S') wrong_answer("Output contains other character than P or S");

  rep(i,0,n) {
    int same = 0, other = 0;
    for (int v : G[i]) {
      if (ans[i] == ans[v]) same++;
      else other++;
    }
    if (same > other) {
      wrong_answer("Student %d has %d friends playing same instrument, %d play other", i, same, other);
    }
  }

  
  string trailing;
  if (author_out >> trailing) wrong_answer("Trailing output");
  accept();
}

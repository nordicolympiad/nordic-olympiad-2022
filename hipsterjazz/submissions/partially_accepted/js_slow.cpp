#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(it,x) for(auto& it : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<typename T, typename S> ostream& operator<<(ostream& os, const pair<T, S> &v) { return os << v.first << " " << v.second; }
template<typename T, typename S> istream& operator>>(istream& is, const pair<T, S> &v) { return is >> v.first >> v.second; }
template<typename T> ostream& operator<<(ostream& os, const vector<T> &v) { rep(i,0,sz(v)) { if (i) os << " " << v[i]; else os << v[i]; } os << endl; return os; }
template<typename T> istream& operator>>(istream& is, vector<T> &v) { trav(it, v) is >> it; return is; }
template<typename T> using v = vector<T>; template<typename T> using vv = v<v<T>>; template<typename T> using vvv = v<v<v<T>>>;
template<typename T> std::vector<T> make(T init, std::size_t size) { return std::vector<T>(size, init); }
template<typename T, typename... Args> auto make(T init, std::size_t first, Args... sizes) { auto inner = make<T>(init, sizes...); return std::vector<decltype(inner)>(first, inner); }
template<typename A, typename B> auto smax(A& a, const B& b) { if (b > a) a = b; }
template<typename A, typename B> auto smin(A& a, const B& b) { if (b < a) a = b;}
bool within(int r, int c, int R, int C) { return 0 <= r && r < R && 0 <= c && c < C; }

vector<vi> G;
vector<bool> side;

void solve() {
  int N, M;
  cin >> N >> M;
  G.resize(N);
  side.resize(N);
  rep(i,0,M) {
    int a, b;
    cin >> a >> b;
    --a; --b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
again:;
  rep(i,0,N) {
    int otherside = 0;
    int sameside = 0;
    trav(it, G[i]) {
      if (side[i] != side[it]) otherside++;
      else sameside++;
    }
    if (sameside > otherside) {
      side[i] = !side[i];
      goto again;
    }
  }
  for (const bool& it : side) {
    cout << "PS"[it];
  }
  cout << endl;
  
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int TC = 1;
  if (!TC) cin >> TC;
  rep(i,1,TC+1) {
    // cout << i << " ";
    solve();
  }
}


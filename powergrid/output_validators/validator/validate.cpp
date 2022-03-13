#include <vector>
#include <algorithm>
#include "validate.h"

using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double ld;

void TOUPPER(string &s){
    for (char& c : s) c = (char)toupper(c);
}

void check_case(){
    int n,m;
    judge_in >> n >> m;
    vector<vi> C(n, vi(m));
    for(int c1 = 0; c1 < n; c1++){
        for(int c2 = 0; c2 < m; c2++){
            judge_in >> C[c1][c2];
        }
    }
    
    string judge, author;
    judge_ans >> judge;

    if(!(author_out >> author)){
        wrong_answer("Could not read first line of input");
    }
    TOUPPER(judge);
    TOUPPER(author);
    if(author != "YES" && author != "NO"){
        wrong_answer("First line of output wasn't 'yes' or 'no'");
    }
    if(author == "NO"){
        if(judge == "YES"){
            wrong_answer("Output was 'no' but judge found a solution");
        }
        return;
    }

    vector<vi> A(n, vi(m));
    for(int c1 = 0; c1 < n; c1++){
        for(int c2 = 0; c2 < m; c2++){
            if(!(author_out >> A[c1][c2])){
                wrong_answer("Could not read item at (%d, %d)", c1+1, c2+1);
            }
        }
    }
    vi row_sum(n, 0);
    vi col_sum(m, 0);
    for(int c1 = 0; c1 < n; c1++){
        int sum = 0;
        for(int c2 = 0; c2 < m; c2++){
            sum += A[c1][c2];
        }
        row_sum[c1] = sum;
    }
    for(int c2 = 0; c2 < m; c2++){
        int sum = 0;
        for(int c1 = 0; c1 < n; c1++){
            sum += A[c1][c2];
        }
        col_sum[c2] = sum;
    }

    for(int c1 = 0; c1 < n; c1++){
        for(int c2 = 0; c2 < m; c2++){
            if(abs(row_sum[c1] - col_sum[c2]) != C[c1][c2]){
                wrong_answer("Rowsum %d and columnsum %d did not correspond to C", c1+1, c2+1);
            }
        }
    }

    if(judge == "NO"){
        judge_error("Judge says 'no' but contestants solution was valid.\n");
    }
}

int main(int argc, char **argv) {
  init_io(argc, argv);
  check_case();

  /* Check for trailing output. */
  string trash;
  if (author_out >> trash) {
      wrong_answer("Trailing output\n");
  }

  accept();
  return 0;
}
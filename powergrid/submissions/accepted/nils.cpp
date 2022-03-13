#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int MAXN = 1002;

int C[MAXN][MAXN] = {0};
int n,m;

bool diff_row[MAXN] = {0};
bool diff_col[MAXN] = {0};
int last_row = -1;
int last_col = -1;

int row_sum[MAXN] = {0};
int col_sum[MAXN] = {0};

bool solve(int i1, int i2, int a, int b){
    // Solve when not all rows and not all columns are identical
    vector<bool> taken_row(n, 0);
    vector<bool> taken_col(m, 0);

    row_sum[last_row] = 0;
    taken_row[last_row] = 1;

    col_sum[i1] = a;
    col_sum[i2] = b;
    taken_col[i1] = 1;
    taken_col[i2] = 1;

    rep(c1,0,n){
        if(!taken_row[c1]){
            int x = a+C[c1][i1];
            int y = a-C[c1][i1];

            if(abs(x-b) == C[c1][i2]){
                row_sum[c1] = x;
                taken_row[c1] = 1;
            }
            if(abs(y-b) == C[c1][i2]){
                row_sum[c1] = y;
                taken_row[c1] = 1;
            }
            if(!taken_row[c1])return 0;
        }
    }

    rep(c1,0,m){
        if(!taken_col[c1]){
            int x = row_sum[0] + C[0][c1];
            int y = row_sum[0] - C[0][c1];

            rep(c2,0,n){
                int x2 = row_sum[c2] + C[c2][c1];
                int y2 = row_sum[c2] - C[c2][c1];
                if(x != x2 && x != y2)x = -111111;
                if(y != x2 && y != y2)y = -111111;
            }
            if(x != -111111){
                col_sum[c1] = x;
                taken_col[c1] = 1;
            }
            if(y != -111111){
                col_sum[c1] = y;
                taken_col[c1] = 1;
            }
            if(!taken_col[c1])return 0;
        }
    }

    int total = 0;
    rep(c1,0,n){
        total += row_sum[c1];
    }
    rep(c1,0,m){
        total -= col_sum[c1];
    }

    if(n == m && total != 0)return 0;
    if(total == 0)return 1;
    if(abs(total) % abs(n-m) != 0)return 0;
    int x = -total / (n-m);

    rep(c1,0,n){
        row_sum[c1] += x;
    }
    rep(c1,0,m){
        col_sum[c1] += x;
    }
    return 1;
}


bool solve_same(){
    // Solve the problem when all numbers C[i][j] are the same.
    int a = C[0][0];
    if(a == 0){
        rep(c1,0,n){
            row_sum[c1] = 0;
        }
        rep(c1,0,m){
            col_sum[c1] = 0;
        }
        return 1;
    }
    int lim = MAXN*MAXN;
    for(int x = -lim; x <= lim; x++){
        int nmx = (n-m)*x;
        if(abs(nmx) % a == 0 && (abs(nmx / a + m))%2 == 0){
            int k = (nmx / a + m) / 2;
            if(k < 0 || k > m)continue;
            rep(c1,0,n){
                row_sum[c1] = x;
            }
            rep(c1,0,m){
                if(c1 < k){
                    col_sum[c1] = x+a;
                }
                else{
                    col_sum[c1] = x-a;
                }
            }
            return 1;
        }
        if(abs(nmx) % a == 0 && (abs(-nmx / a + n))%2 == 0){
            int k = (-nmx / a + n) / 2;
            if(k < 0 || k > n)continue;
            rep(c1,0,m){
                col_sum[c1] = x;
            }
            rep(c1,0,n){
                if(c1 < k){
                    row_sum[c1] = x+a;
                }
                else{
                    row_sum[c1] = x-a;
                }
            }
            return 1;
        }
    }
    return 0;
}

const int MAX_SUM = 2*MAXN*MAXN;  // <--- can be halved, but its a bit more effort
vector<bool> subsetsum(vi W, vi goals){
    vector<bitset<MAX_SUM> > DP(sz(W), bitset<MAX_SUM>());
    rep(c1,0,sz(W)){
        if(c1 == 0){
            DP[c1][0] = 1;
            DP[c1][W[c1]] = 1;
        }
        else{
            DP[c1] = (DP[c1-1] | (DP[c1-1] << W[c1]));
        }
    }
    int goal = -1;
    trav(y, goals){
        if(DP[sz(W)-1][y]){
            goal = y;
            break;
        }
    }
    if(goal == -1)return {};
    vector<bool> res(sz(W), 0);
    for(int c1 = sz(W)-1; c1 >= 0; c1--){
        if(goal == 0)break;
        if(c1 == 0){
            res[0] = 1;
        }
        else{
            if(DP[c1][goal] && !DP[c1-1][goal]){
                res[c1] = 1;
                goal -= W[c1];
            }
        }
    }
    return res;
}

bool same_column(){
    // Solve when all rows are identical but not all columns
    vi W, goals;
    int tot = 0;
    rep(c1,0,m){
        tot += C[0][c1];
        W.push_back(2*C[0][c1]);
    }
    int nm = abs(n-m);

    rep(c1,-tot,tot+1){
        if(c1 * nm + tot >= 0 && c1 * nm + tot <= 2*tot){
            goals.push_back(c1 * nm + tot);
        }
    }

    vector<bool> SS = subsetsum(W, goals);
    if(sz(SS) == 0)return 0;
    int ss = 0;
    rep(c1,0,m){
        if(SS[c1]){
            ss += C[0][c1];
        }
        else{
            ss -= C[0][c1];
        }
    }
    int x = 0;
    if(n == m){
        assert(ss == 0);
    }
    else{
        assert(abs(ss) % abs(n-m) == 0);
        x = ss / (n-m);
    }
    rep(c1,0,n){
        row_sum[c1] = x;
    }
    rep(c1,0,m){
        if(SS[c1]){
            col_sum[c1] = x + C[0][c1];
        }
        else{
            col_sum[c1] = x - C[0][c1];
        }
    }
    return 1;
}

int ANS[MAXN][MAXN] = {0};
void get_grid(){
    // Generate the grid from row_sum and col_sum
    priority_queue<pii> row_pq, col_pq;
    rep(c1,0,n){
        row_pq.push({abs(row_sum[c1]), c1});
    }
    rep(c1,0,m){
        col_pq.push({abs(col_sum[c1]), c1});
    }
    while(1){
        int i = row_pq.top().second;
        row_pq.pop();
        int j = col_pq.top().second;
        col_pq.pop();
        if(abs(row_sum[i]) + abs(col_sum[j]) == 0)break;
        if(abs(row_sum[i]) > abs(col_sum[j])){
            ANS[i][j] += row_sum[i];
            col_sum[j] -= row_sum[i];
            row_sum[i] = 0;
        }
        else{
            ANS[i][j] += col_sum[j];
            row_sum[i] -= col_sum[j];
            col_sum[j] = 0;
        }
        row_pq.push({abs(row_sum[i]), i});
        col_pq.push({abs(col_sum[j]), j});
    }
}

bool verify_solution(){
    // Check that the solution is valid (this is not necessary)
    vi row, col;
    rep(c1,0,n){
        int sum = 0;
        rep(c2,0,m){
            sum += ANS[c1][c2];
        }
        row.push_back(sum);
    }
    rep(c2,0,m){
        int sum = 0;
        rep(c1,0,n){
            sum += ANS[c1][c2];
        }
        col.push_back(sum);
    }
    rep(c1,0,n){
        rep(c2,0,m){
            if(abs(row[c1]-col[c2]) != C[c1][c2])return 0;
        }
    }
    return 1;
}

bool flipped = 0;
void flip(){
    rep(c1,0,max(n,m)){
        rep(c2,0,c1){
            swap(C[c1][c2], C[c2][c1]);
        }
    }
    swap(n,m);
    swap(row_sum, col_sum);
    flipped ^= 1;
}

int main() {

    cin >> n >> m;
    rep(c1,0,n){
        rep(c2,0,m){
            cin >> C[c1][c2];
        }
    }
    rep(c1,0,n){
        rep(c2,0,m){
            if(C[c1][c2] != C[c1][0]){
                diff_row[c1] = 1;
                last_row = c1;
            }
        }
    }
    rep(c2,0,m){
        rep(c1,0,n){
            if(C[c1][c2] != C[0][c2]){
                diff_col[c2] = 1;
                last_col = c2;
            }
        }
    }

    bool fail = 0;

    if(last_col != -1 && last_row != -1){
        int i1 = last_col;
        int i2 = 0;
        rep(c1,0,m){
            if(C[last_row][c1] != C[last_row][i1]){
                i2 = c1;
                break;
            }
        }
        bool solved = 0;
        if(solve(i1, i2, -C[last_row][i1], -C[last_row][i2])){solved = 1; goto done;}
        if(solve(i1, i2, -C[last_row][i1], C[last_row][i2])){solved = 1; goto done;}
        if(solve(i1, i2, C[last_row][i1], -C[last_row][i2])){solved = 1; goto done;}
        if(solve(i1, i2, C[last_row][i1], C[last_row][i2])){solved = 1; goto done;}
        done:
        if(!solved){
            fail = 1;
        }
    }
    else{
        if(last_col == -1 && last_row == -1){
            fail = !solve_same();
        }
        else{
            if(last_row == -1)flip();
            fail = !same_column();
            if(flipped)flip();
        }
    }

    if(!fail){
        cout << "YES\n";
        get_grid();
        rep(c1,0,n){
            rep(c2,0,m){
                cout << ANS[c1][c2] << " ";
            }cout << "\n";
        }
        assert(verify_solution());
    }
    else{
        cout << "NO\n";
    }
    return 0;
}

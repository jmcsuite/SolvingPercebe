#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 16;
const int maxm = 101;

ll dp[maxm][2];
string vl[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M; cin >> N >> M;
    for (int i = N-1; i >= 0; i--) cin >> vl[i];
    
    for (int i = 0; i < N; i++) {

        int der = 0; 
        for (size_t j = 0; j < vl[i].size(); j++) {
            if (vl[i][j] == '1') der = j;
        }
        int izq = M+1;

        for (int j = M; j >= 0; j--) {
            if (vl[i][j] == '1') izq = j;
        }

        izq = M+1 - izq;  

        if (i == 0) {
            dp[i][0] = der*2;
            dp[i][1] = M+1;
        }
        else {
            dp[i][0] = min(der*2 + dp[i-1][0] + 1, dp[i-1][1]+M+2);
            dp[i][1] = min(dp[i-1][0] + M + 2, dp[i-1][1] + izq*2 + 1);
        }
    }

    int nn = 0;
    for (int i = 0; i < N; i++) {
        bool se = false;
        for (size_t j = 0; j < vl[i].size(); j++) if (vl[i][j] == '1') se = true;
        if (se) nn = i;
    }
    N = nn+1;

    if (N == 0) {
        cout << 0 << '\n';
        return 0;
    }


    if (N == 1) {
        int der = 0;
        for (size_t j = 0; j < vl[0].size(); j++) {
            if (vl[0][j] == '1') der = j;
        }
        cout << der << '\n';
        return 0;
    }

    
    int i = N-1;
    int der = 0; 
    for (size_t j = 0; j < vl[i].size(); j++) {
        if (vl[i][j] == '1') der = j;
    }
    int izq = M+1;

    for (int j = M; j >= 0; j--) {
        if (vl[i][j] == '1') izq = j;
    }

    izq = M+1 - izq;  
    ll ans = min(dp[N-2][0] + der, dp[N-2][1] + izq) + 1;
    cout << ans << '\n';
}

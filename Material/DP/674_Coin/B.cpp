#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 7490;
const int maxm = 5;

ll dp[maxn][maxm];
ll coins[maxm] = {50, 25, 10, 5, 1};

ll formas(ll s, ll j) {
    if (s < 0) return 0;
    if (s == 0) return 1;
    if (j >= maxm) return 0;

    // dp 
    if (dp[s][j] != -1) return dp[s][j];

    ll ans = formas(s-coins[j], j) + formas(s, j+1);
    return dp[s][j] = ans;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    for (int i = 0; i < maxn; i++) for(int j = 0; j < maxm; j++) dp[i][j] = -1;
    ll N;
    while (cin >> N) {
        cout << formas(N,0) << '\n';
    }
}

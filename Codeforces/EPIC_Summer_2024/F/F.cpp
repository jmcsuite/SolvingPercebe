#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int maxn = 100;

ll vl[maxn];
ll dp[maxn][maxn][maxn];
ll N;

ll F(ll l, ll r, ll d) {
    if (l >= r) return 0;
    if (dp[l][r][d] != -1) return dp[l][r][d];
    ll ans = F(l+1, r, d);
    if (vl[l] > l) return dp[l][r][d] = ans;
    if (vl[l] % 2 != l%2) return dp[l][r][d] = ans;
    if (l - d > vl[l]) return dp[l][r][d] = ans;

    ll dmin = min(d, (l - vl[l]));
    for (int j = r; j > l; j--) {
        ll d2 = F(l+1, j-1, dmin);
        if ((d2 * 2) == (j - l -1)) ans = max(ans, 1 + d2 + F(j+1, r, d+(j-l+1)));
    }
    return dp[l][r][d] = ans;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; i++) cin >> vl[i];
        for (int i = 0; i < N; i++) vl[i]--;
        for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) for (int k = 0; k < N; k++) dp[i][j][k] = -1;
        cout << F(0,N-1,0) << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 203;



ll dp[maxn][maxn];
ll f[maxn][maxn][maxn];

ll n,m,c;
ll a[maxn][maxn];

ll func(ll i, ll j, ll k);
ll calc(ll i, ll j);

ll calc(ll i, ll j) {
    if (dp[i][j] != -1) return dp[i][j];
    dp[i][j] = 1e18;
    for (int k=0; k<m; k++) {
        dp[i][j] = min(dp[i][j], k*c + func(i,j,k));
    }
    return dp[i][j];
}

ll func(ll i, ll j, ll k) {
    if (f[i][j][k] != -1) return f[i][j][k];
    f[i][j][k] = a[i][(j+k)%m];
    if (i == n-1 && j == m-1) return f[i][j][k];
    if (j == m-1) return f[i][j][k] = f[i][j][k] + calc(i+1,j);
    if (i == n-1) return f[i][j][k] = f[i][j][k] + func(i,j+1,k);
    f[i][j][k] += min(calc(i+1, j), func(i,j+1,k));
    return f[i][j][k];
}

void solve() {
    cin >> n >> m >> c;
    for (int i=0; i<n; i++) for (int j=0; j<m; j++) cin >> a[i][j];
    for (int i=0; i<=n+1; i++) for (int j=0; j<=m+1; j++) dp[i][j] = -1;

    for (int i=0; i<=n+1; i++) {
        for (int j=0; j<=m+1; j++) {
            for (int k=0; k<=m+1; k++) f[i][j][k] = -1;
        }
    }

    cout << calc(0,0) << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t; 
    while (t--) solve();
}

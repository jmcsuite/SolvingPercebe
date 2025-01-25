#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e5;
const int maxm = 10;
ll dp[maxn][maxm+1];
ll vl[maxn];
ll b[maxm];
ll mask[1<<maxm];

void solve() {
    ll n,m,k; 
    cin>>n>>m>>k;
    for (int i=0; i<n; i++) cin>>vl[i];
    for (int i=0; i<m; i++) cin>>b[i];
    for (int i=0; i<(1<<m); i++) {
        mask[i] = (1ll<<30)-1;
        for (int j=0; j<m; j++) if (((1<<j)&i)) mask[i] &= b[j];
    }

    for (int i=0; i<n; i++) for(int j=0; j<=maxm; j++) dp[i][j] = vl[i];

    for (int i=0; i<n; i++) {
        for (int j=0; j<(1<<m); j++) {
            ll p = __builtin_popcount(j);
            dp[i][p] = min(dp[i][p], vl[i] & mask[j]);
        }
    }

    vll ans(n*m);
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) ans[i*m + j] = dp[i][j] - dp[i][j+1];
    }
    sort(ans.rbegin(), ans.rend());
    ll sol = 0;
    for (int i=0; i<n; i++) sol += vl[i];
    for (int i=0; i<k; i++) sol -= ans[i];
    cout << sol << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}

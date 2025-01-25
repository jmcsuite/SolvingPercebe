#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e5 + 1;
const int mod = 998244353;

ll dp[maxn];
ll vl[maxn];
void solve() {
    ll n; cin>>n;
    for (int i=0; i<n; i++) cin>>vl[i];
    for (int i=0; i<=n; i++) dp[i] = 0;

    for (int i=0; i<n; i++) vl[i] = i - vl[i];

    for (int i=0; i<n; i++) {
        if (vl[i] < 0) continue;
        if (i == 0) {
            dp[i] = (vl[i] == 0 ? 1 : 0);
            continue;
        }
        dp[i] = (vl[i] - vl[i-1] == 1 ? dp[i-1] : 0);
        if (i == 1) {
            dp[i] += (vl[i] == 0 ? 1 : 0);
            continue;
        }
        dp[i] += (vl[i] - vl[i-2] == 1 ? dp[i-2] : 0);
        dp[i] %= mod;
    }

    ll ans = dp[n-1];
    if (n > 1) ans += dp[n-2];
    else ans++;
    ans %= mod;
    cout << ans << '\n';
}
    
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}

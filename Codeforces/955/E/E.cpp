#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxk = 62;
const int mod = 1e9 + 7;

ll dp[maxk][maxk];

ll pp[maxk + 1];

void fill () {
    pp[0] = 1;
    for (int i = 1; i <= maxk; i++) pp[i] = (pp[i-1] * 2) % mod;
    for (int i = 0; i < maxk; i++) dp[i][0] = 1;
    for (int i = 0; i < maxk; i++) dp[0][i] = 1;

    for (ll m = 1; m < maxk; m++) {
        for (ll k = 1; k < maxk; k++) {
            dp[m][k] = (dp[m-1][k] + dp[m-1][k-1])%mod;
            ll x = (m-1 <= k ? 0ll : pp[m-1]);
            ll xend = pp[m-1];
            ll ybegin = pp[m-1];
            ll y = (k >= m ? pp[m] : pp[m-1] + pp[k] - 1);

            ll dy = (y - ybegin) % mod;
            ll dx = (xend - x) % mod;
            dp[m][k] = (dp[m][k] + dy*dx)%mod;
        }
    }
}


ll solve(ll n, ll k) {
    if (n == 0) return 0;
    if (k == 0) return 1;
    ll y = 1; 
    while (y < n - y) y *= 2;
    n -= y;
    ll x = __builtin_ctzll(y);
    ll ans = dp[x][k];
    ll bx = (x <= k ? 0ll : pp[x]);
    ll ex = pp[x];
    ll by = pp[x];

    ll ey = (k >= x+1 ? y*2 : y + (1ll << k) - 1);
    ey = min(n + y , ey);

    ll dy = (ey - by) % mod;
    ll dx = (ex - bx) % mod;
    ans = (ans + dy*dx)%mod;
    ans = (ans + solve(n, k-1)) % mod;
    return ans;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fill();
    ll T; cin >> T; 
    while (T--) {
        ll N, K; cin >> N >> K;
        ll ans = solve(N, K); 
        ans %= mod;
        ans += mod;
        ans %= mod;
        cout << ans << '\n';
    }
}

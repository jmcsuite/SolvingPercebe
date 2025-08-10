#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 3e3 + 10;
const int mod = 998244353;
const int cero = maxn;

ll dp[2*maxn][2];
ll tmp[2*maxn][2];
ll prob;
ll invprob;
ll bin_exp(ll a, ll x) {
    ll ans = 1;
    while (x) {
        if (x%2) ans = (a*ans)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

void nstep() {
    for (int i=0; i<2*maxn; i++) dp[cero][0] = (dp[cero][0] + dp[i][1]) % mod;
    for (int i=0; i<2*maxn; i++) dp[i][1] = 0;
}

void diff(ll steps) {
    for (int k=0; k<steps; k++) {
        for (int i=0; i<2*maxn; i++) tmp[i][0] = tmp[i][1] = 0;
        for (int i=1; i+1 < 2*maxn; i++) {
            tmp[i+1][1] = (tmp[i+1][1] + dp[i][1] * prob)%mod;
            tmp[i-1][1] = (tmp[i-1][1] + dp[i][1] * invprob)%mod;
            tmp[i+1][0] = (tmp[i+1][0] + dp[i][0] * prob)%mod;
            int d = (i == cero ? 1 : 0);
            tmp[i-1][d] = (tmp[i-1][d] + dp[i][0] * invprob)%mod;
        }
        swap(tmp, dp);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll p,q; cin>>p>>q;
    prob = (p * bin_exp(q,mod-2))%mod;
    invprob = (1 + mod - prob) % mod;
    //prob = invprob = 1;
    dp[cero][0] = 1;

    ll n; cin>>n;
    vll vl(n+1);
    for (int i=1; i<=n; i++) cin>>vl[i];
    reverse(vl.begin(), vl.end());
    for (int i=1; i<=n; i++) {
        nstep();
        diff(vl[i-1] - vl[i]);
    }
    ll ans = 0;
    for (int i=0; i<2*maxn; i++) ans = (ans + dp[i][1])%mod;
    cout << ans << '\n';
}

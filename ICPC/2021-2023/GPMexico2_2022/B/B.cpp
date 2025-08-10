#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxc = 50;
ll dp[maxc];
void calc() {
    dp[0] = 0;
    dp[1] = 1;
    for (int i=2; i<maxc; i++) {
        if(i%2 == 0) dp[i] = dp[i-1];
        else dp[i] = dp[i-1]*2;
    }
    for (int i=1; i<maxc; i++) dp[i] += dp[i-1];
}

ll ff(ll x) {
    if (x < 0) return 0;
    if (x == 1) return 1;
    if (x == 0) return 0;
    ll c = 0;
    while ((1ll<<c) <= x) c++;
    ll k = c/2;
    ll sum = 0;
    ll pal = 0;
    for (int i = c-1,j=0; j<k; j++,i--) {
        sum |= (x&(1ll<<i));
        pal |= ( (x&(1ll<<i)) ? (1ll<<j) : 0ll);
    }
    if (c%2) pal |= (x&(1ll<<k));
    ll cant = (sum >>(c-k)) - (1ll<<(k-1)) + 1;

    ll ans = cant;
    if (pal + sum > x) ans--;
    if ( (c%2 == 1) && (x&(1ll<<k))) ans+=cant;
    else if ((c%2 == 1)) ans += cant -1;
    ans += dp[c-1];
    return ans;
}

void solve() {
    ll a,b; cin>>a>>b;
    --a;
    cout << ff(b) - ff(a) << '\n';
}

int main() {
    calc();
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n; cin>>n;
    while(n--) solve();
}

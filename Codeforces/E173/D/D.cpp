#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b%a, a);
}

ll ff(ll x, ll r) {
    for (ll i = r; i>=x; i--) {
        if (gcd(i,x) == 1) return i;
    }
    return -1;
}

pll solve() {
    ll l,r,G; cin>>l>>r>>G;
    r = r/G;
    l = (l+G-1) / G;

    pll ans(-1, -1);
    for (ll i=l; i<=r; i++) {
        ll p = ff(i, r);
        if (p == -1) continue;
        if (ans.first == -1 || (ans.second - ans.first < (p*G - i*G))) {
            ans.first = i*G;
            ans.second = p*G;
        }
        if (p >= r-1) return ans;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) {
        pll p = solve();
        cout << p.first << ' ' << p.second << '\n';
    }
}

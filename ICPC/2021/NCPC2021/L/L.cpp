#include <bits/stdc++.h>
using namespace std;
using ll = long long;


ll gcd(ll a, ll b) {
    if (b == 0) return a;
    if (a == 0) return b;
    return gcd(b%a, a);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll Q; cin >> Q;
    ll ans = 1e17;
    while (Q--) {
        ll x; ll a,b;
        cin >> x >> a >> b;
        ll n = (a*b) / gcd(a,b);
        ans = min(ans, x+n);
    }
    cout << ans << '\n';
}

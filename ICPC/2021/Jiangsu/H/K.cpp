#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll has_m(ll m) {
    ll p = 1 + 1; // 0 and 2^m
    for (ll i = 1; i <= m; i++) {
        p = p + i*(1ll<<(i-1));
    }
    return p;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll x; cin >> x;
        ll ans = 0;
        for (ll i=0; has_m(i) <= x; i++) ans=i+1;
        cout << ans << '\n';
    }
}

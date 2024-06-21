#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll x,y,z,k; cin >> x >> y >> z >> k;
        ll ans = 0;
        for (ll i = 1; i <= x; i++) {
            for (ll j = 1; j <= y; j++) {
                ll p = (k) / (i*j);
                if (k != i*j*p) continue;
                if (p > z) continue;
                ans = max(ans, ((x-i+1)*(y-j+1)*(z-p+1)));
            }
        }
        cout << ans << '\n';
    }
}

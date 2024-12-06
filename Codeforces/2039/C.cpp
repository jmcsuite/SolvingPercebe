#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll T; cin >> T;
    while (T--) {
        ll x,m; cin >> x >> m;
        ll ans = 0;

        for (ll i=1; i<=2*x; i++) {
            if (i > m) break;
            if (i == x) continue;
            ll y = i^x;
            if (x%y == 0 || i%y == 0) ans++;
        }
        cout << ans << '\n';
    }
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll a,b; cin >> a >> b;
        ll x = a^b;
        ll ans = 1;
        while ((ans&x) == 0) ans <<= 1;
        cout << ans << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;

ll exp(ll a, ll x) {
    ll ans = 1;
    while (x) {
        if (x%2) ans = (ans * a) % mod;
        a = (a * a) % mod;;
        x /= 2;
    }
    return ans;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll a,b,c; cin >> a >> b >> c;
        if (c >= 10) {
            cout << 0 << '\n';
            continue;
        }
        ll v = (9 / c) + 1;
        cout << ((((exp(v, b) - exp(v, a)) % mod ) + mod) % mod) << '\n';
    }
}

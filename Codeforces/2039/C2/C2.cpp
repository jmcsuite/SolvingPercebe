#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e6;
ll x, M;

ll howMany(ll bits, ll mod) {
    mod %= x;
    ll nums = (1ll << bits) - 1;
    nums -= mod;
    if (nums < 0) return 0;
    return (nums / x) + 1;
}

ll dp() {
    ll ans = 0;
    ll mod = 0;

    for (ll i = 60; i >= 0; i--) {
        ll ti = (1ll << i);
        ll xorPut = (x & ti);
        ll xorPos = (ti & M);

        if (xorPos == 0) {
            if (xorPut) mod = (mod + (ti%x)) % x;
            continue;
        }

        if (xorPut) {
            ans += howMany(i,x - ((mod + (ti)%x)%x));
        }
        else {
            ans += howMany(i, x - mod);
            mod = (mod + (ti%x))%x;
        }
    }
    if (mod == 0) ans++;
    return ans;
}


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;

    while (T--) {
        cin >> x >> M;
        ll ans = dp();
        ans--;

        for (ll y = 1; y <= 2*x; y++) {
            if (y > M) break;
            ll u = x^y;
            if (u%x == 0) continue;
            if (u%y == 0) ans++;
        }
        cout << ans << '\n';
    }
}

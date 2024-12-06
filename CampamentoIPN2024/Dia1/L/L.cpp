#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll guess(ll x) {
    cout << "? " << x << endl;
    ll a; cin >> a;
    return a;
}

ll pp(ll a, ll x) {
    ll ans = 1;
    while (x) {
        if (x%2) ans = ans * a;
        a = a*a;
        x/=2;
    }
    return ans;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll ndigits; cin >> ndigits;

    ll ans = 0;
    ll bit = (1ll<<44);
    while (bit) {
        if (guess(ans+bit) <= ndigits) ans += bit;
        bit >>= 1;
    }
    ll b = ans + 1;

    ans = 0;
    bit = (1ll<<54);
    while (bit) {
        if (guess(ans+bit+b) <= (ndigits+1)) ans += bit;
        bit >>= 1;
    }
    ll c = ans + 1;

    //cout << c << endl;
    for (ll i = 2; i <= 2023; i++) {
        //cout << pp(i, ndigits+2) - pp(i,ndigits+1) << endl;
        if (pp(i, ndigits+1) - pp(i, ndigits) != c) continue;
        ll x = pp(i, ndigits) - b;
        cout << "! " << x << ' ' << i << endl;
        return 0;
    }
}

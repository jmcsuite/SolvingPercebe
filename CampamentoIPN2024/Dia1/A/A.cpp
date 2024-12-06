#include <bits/stdc++.h>
using namespace std;
using ll = long long;


ll sqr(ll x) {
    ll ans = 0;
    ll delta = 1e9;
    while (delta != 0) {
        if ((ans + delta) * (ans + delta) > x) delta /= 2;
        else ans += delta;
    }
    return ans;
}

ll tc(double x) {
    ll y = (ll)(x*x);
    ll ans = 0;
    for (ll i = 1; i*i < y; i++) {
        ans += sqr(y - (i*i));
    }
    return ans*4;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    double ans = 1e5;
    double delta = 1e5;
    while (delta > 1e-7) {
        if (tc(ans - delta) <= N) delta /= 2;
        else ans -= delta; 
    }
    cout << fixed << setprecision(7) << ans << '\n';
}


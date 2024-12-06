#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll mod;
ll bin_exp(ll a, ll x) {
    ll ans = 1;
    while (x) {
        if (x%2) ans = (ans*a)%mod;
        x/=2;
        a = (a*a)%mod;
    }
    return ans;
}



int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N;
    while (cin>>mod>>N, mod) {
        for (ll i = 0; i<N; i++) {
            ll a; cin >> a;
            if (mod == 2) {
                cout << "YES\n";
                continue;
            }

            ll div = mod-1;
            bool se = true;
            for (ll j=1; j*j <= div; j++) {
                if (div%j) continue;
                if (bin_exp(a, j) == 1) se=false;
                if (div/j != div && bin_exp(a, div/j) == 1) se=false;
            }
            if (se) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}

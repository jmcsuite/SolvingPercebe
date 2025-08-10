#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5;
const int mod = 1e9 + 7;
ll vl[maxn];

void solve() {
    ll n; cin>>n;
    for (int i=0; i<n; i++) cin>>vl[i];
    map<ll,ll> mp;
    mp[0] = 1;
    ll p = 0;
    
    for (int i=0; i<n; i++) {
        ll vp = mp[p] % mod;
        ll va = mp[vl[i] ^ p] % mod;
        mp[p] = 3*vp;
        mp[p] += 2*va;
        mp[vl[i]^p] = va;
        p = vl[i] ^ p;
    }
    ll ans = 0;
    for (auto pa : mp) ans = (ans + pa.second) % mod;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while (t--) solve();
}

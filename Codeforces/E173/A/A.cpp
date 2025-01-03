#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

void solve() {
    ll x; cin>>x; 
    ll ans = 0;
    while (x > 3) {
        x /= 4;
        ans++;
    }
    cout << (1ll<<ans) << '\n';
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) solve();
}

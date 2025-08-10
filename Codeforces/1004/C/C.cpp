#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool check(ll x) {
    while (x > 0) {
        if (x%10 == 7) return true;
        x/=10;
    }
    return false;
}

ll tt(ll x, ll a) {
    ll ans = 0;
    while (!check(x)) {
        ans++;
        x += a;
    }
    return ans;
}


void solve() {
    ll x; cin>>x;
    ll ans = 11;
    ll a = 9;
    for (int i=0; i<11; i++) {
        ans = min(ans,tt(x,a));
        a = a*10 + 9;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}

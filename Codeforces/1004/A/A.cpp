#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

void solve() {
    ll x,y; cin>>x>>y;
    if (x == y) cout << "NO\n";
    if (x == y) return;

    if (y > x) {
        if (y == x+1) cout << "YES\n";
        else cout << "NO\n";
        return;
    }

    ll delta = x - y + 1;
    if (delta % 9 == 0) cout << "YES\n";
    else cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while (T--) solve();
}

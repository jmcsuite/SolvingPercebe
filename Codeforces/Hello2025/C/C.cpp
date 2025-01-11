#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll l,r; cin>>l>>r;
    ll a,b,c; 
    a = b = c = 0;
    bool dif = false;
    for (ll i = 32; i>=0; i--) {
        if (dif) {
            a |= (1ll << i);
            continue;
        }
        if ((l&(1ll<<i)) == (r&(1ll<<i))) {
            a |= (l&(1ll<<i));
            b |= (l&(1ll<<i));
            continue;
        }
        dif = true;
        b |= (1ll<<i);
    }

    c = l;
    if (c == a || c == b) c++;
    if (c == a || c == b) c++;
    cout << a << ' ' << b << ' ' << c << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--) solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 1e6 + 10;
ll vl[maxn];

void solve() {
    ll n,l,r,c; cin>>n>>l>>r>>c;
    for (int i=0; i<n; i++) cin>>vl[i];
    if (c < l || c > r) {
        cout << -1 << '\n';
        return;
    }
    ll leq = 0;
    ll eq = 0;
    ll meq = 0;
    for (int i=0; i<n; i++) {
        if (vl[i] == c) eq++;
        if (vl[i] <= c) leq++;
        if (vl[i] >= c) meq++;
    }


    ll cost = (eq == 0 ? 1 : 0);
    ll need = n - n/2;
    ll c1 = max(cost, need - leq);
    if (n%2 == 0) need++;
    ll c2 = max(c1, need - meq);
    cout << c2 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}

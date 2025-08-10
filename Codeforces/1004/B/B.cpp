#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e3;
ll vl[maxn];

void solve() {
    ll n; cin>>n;
    for (int i=0; i<n; i++) cin>>vl[i];
    sort(vl, vl+n);
    ll pr = 0;
    for (int i=0; i<n; i+=2) {
        ll x = max(pr+1, vl[i]);
        ll x2 = max(pr+1, vl[i+1]);
        if (x != x2) {
            cout << "No\n";
            return;
        }
        pr = x;
    }
    cout << "Yes\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll n; cin>>n;
    ll odd, even; odd = even = 0;
    for (int i=0; i<n; i++) {
        ll x; cin>>x;
        if(x%2) odd++;
        else even++;
    }
    if (even > 0) cout << odd + 1 << '\n';
    else cout << odd-1 << '\n';
}

int main() {
    ll t; cin>>t;
    while(t--) solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll n; cin>>n;
    cout << 1;
    for (int i=1; i<=n-2; i++) cout << ' ' << i;
    cout << ' ' << 1 << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--) solve();
}

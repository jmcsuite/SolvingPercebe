#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--) {
        ll n,a,b; cin>>n>>a>>b;
        ll p = max(a-b, b-a);
        if (p%2) cout << "NO\n";
        else cout << "YES\n";
    }
}

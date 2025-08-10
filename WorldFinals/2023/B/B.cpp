#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n,m; cin>>n>>m;
    double ans;
    for (int i=0; i<n*m; i++) {
        ll x; cin>>x;
        ans += x;
    }
    ans = ans / double(n*m);
    cout << setprecision(8) << fixed;
    cout << ans << '\n';
}

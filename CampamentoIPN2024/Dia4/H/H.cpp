#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll x,y; ll a,b; cin >> x >> y >> a >> b;

    if (x*a < 0 || y*b < 0) cout << 1 << '\n';
    else cout << 0 << '\n';
}

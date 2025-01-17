#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll D,E,F,x,y,H; cin>>D>>E>>F>>x>>y>>H;

    x--; y--;
    ll m = max(D,E);
    for (int i=0; i<m; i++) x/=2;
    for (int i=0; i<m; i++) y/=2;
    while (x != y) {
        x/=2; 
        y/=2;
        m++;
    }

    ll p = F-m;
    ll a = F-D;
    ll b = F-E;

    ll ans = a + b - 2*p;
    if (ans > H) cout << "NO\n";
    else cout << "YES\n";
}

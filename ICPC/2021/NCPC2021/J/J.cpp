#include <bits/stdc++.h>
using namespace std;
using ll = long long;


ll dis(ll x, ll y, ll a, ll b) {
    return (x-a)*(x-a) + (y-b) * (y-b);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll x,y, x2, y2, a, b, a2, b2;
    cin >> x >> y >> a >> b >> x2 >> y2 >> a2 >> b2;
    ll ans = 0;

    ans = max(ans, dis(x,y,a,b));
    //ans = max(ans, dis(x,y,a2,b2));
    //ans = max(ans, dis(x2,y2,a,b));
    ans = max(ans, dis(x2,y2,a2,b2));

    double pp = ans;
    pp = sqrt(pp);
    cout << fixed << setprecision(8) << pp << '\n';
}

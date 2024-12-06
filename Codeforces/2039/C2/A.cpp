#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0); 
    ll T; cin>>T;
    while (T--) {
        ll x,M; cin>>x>>M; 
        ll ans=0;
        for (ll y = 1; y<=x; y++) {
            ll xy = y ^ x;
            if (y > M) break;
            if (xy % x == 0) continue;
            if (xy % y == 0) ans++;
        }

        if (M >= x) ans += (M-x)/x + 1;
        for (ll m = M-x+1; m <= M+x; m++) {
            if (m<0) continue;
            if (m%x) continue;
            ll mx = x ^ m; 
            if (mx > M) continue;
            ans++;
        }

        ans--;
        cout << ans << '\n';
    }
}

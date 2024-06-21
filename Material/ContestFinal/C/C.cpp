#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        ll ans,sum,maxi;
        ans = sum = maxi = 0;
        while (N--) {
            ll a; cin >> a;
            sum += a;
            maxi = max(a, maxi);
            if (sum - maxi == maxi) ans++;
        }
        cout << ans << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        ll ans = 1e9;
        vll vl(N); for (int i = 0; i < N; i++) cin >> vl[i];
        for (int i = 1; i < N; i++) {
            ll b = max(vl[i-1], vl[i]);
            ans = min(ans, b);
        }
        cout << ans-1 << '\n';
    }
}

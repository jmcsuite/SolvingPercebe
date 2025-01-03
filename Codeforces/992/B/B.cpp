#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll N; cin >> N;
    if (N == 1) {
        cout << 1 << '\n';
        return;
    }
    ll sum = 1;
    ll ans = 1;
    while (1) {
        ans++;
        sum++;
        sum*=2;
        if (sum >= N) {
            cout << ans << '\n';
            return;
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        solve();
    }
}

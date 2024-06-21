#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        vector<ll> vl(N);
        for (int i = 0; i < N; i++) cin >> vl[i];
        sort(vl.rbegin(), vl.rend());
        ll ans = 0;
        for (int i = 2; i < N; i+=3) ans += vl[i];
        cout << ans << '\n';
    }
}

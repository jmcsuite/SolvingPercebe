#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, K; cin >> N >> K;
        vll vl(N);
        for (int i=0; i<N; i++) cin >> vl[i];
        sort(vl.rbegin(), vl.rend());
        ll ans = K;
        ll sum = 0;

        for (int i=0; i<N; i++) {
            sum += vl[i];
            if (sum > K) break;
            ans = min(ans, K-sum);
        }
        cout << ans << '\n';
    }
}

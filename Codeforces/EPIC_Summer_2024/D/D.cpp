#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 5001;

ll cant[maxn];
ll pos[maxn];
ll dp[maxn];


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        for (int i = 0; i < maxn; i++) cant[i] = pos[i] = dp[i] = 0;
        ll N; cin >> N;
        for (int i = 0; i < N; i++) {
            ll a; cin >> a;
            cant[a]++;
        }

        ll p = 0;
        for (int i = 0; i <= N; i++) {
            if (cant[i] > 0) p++;
            pos[i] = p;
        }

        for (int i = N; i > 0; i--) {
            if (cant[i] == 0) continue;
            ll d0 = pos[i] - cant[i];
            for (int j = N; j > 1; j--) {
                ll ndn = dp[j-1] - 1 - cant[i];
                ndn = min(ndn, d0);
                dp[j] = max(dp[j], ndn);
            }
            dp[1] = max(dp[1], d0);
        }

        ll ans = 0;
        for (int i = 1; i <= N; i++) {
            if (dp[i] > 0) ans = i;
        }
        cout << p - ans << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 100+1;
const int maxl = 1e4+1;

ll dp[maxl];
ll cp[maxn];
ll wp[maxn];
ll vp[maxn];

ll wk[maxn];
ll vk[maxn];

ll calc(ll v[maxn], ll w[maxn], ll d[maxl], ll W, ll X) {
    memset(d, 0, sizeof(dp));
    for (int i = 0; i < X; i++) {
        for (int j = W - w[i]; j >= 0; j--) {
            d[j+w[i]] = max(d[j+w[i]], d[j] + v[i]);
        }
    }
    ll ans = 0;
    for (int i = 0; i <= W; i++) ans = max(ans, d[i]);
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N, K, L;
    cin >> N >> K >> L;
    for (int i = 0; i < N; i++) cin >> cp[i] >> wp[i];
    for (int i = 0; i < K; i++) cin >> wk[i] >> vk[i];
    
    for (int i = 0; i < N; i++) {
        vp[i] = calc(vk, wk, dp, cp[i], K);
    }
    ll ans = calc(vp, wp, dp, L, N);
    cout << ans << '\n';
}

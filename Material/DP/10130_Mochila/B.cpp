#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1001; 
const int maxg = 31;

ll dp[maxn][maxg];
ll p[maxn];
ll w[maxn];
ll N;

ll f(ll item, ll pes) {
    if (item == N) return 0;

    // memoization
    if (dp[item][pes] != -1) return dp[item][pes];

    ll ans = f(item+1, pes);
    if (w[item] <= pes) ans = max(ans, p[item] + f(item+1, pes - w[item]));

    return dp[item][pes] = ans;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < maxn; i++) for(int j = 0; j < maxg; j++) dp[i][j] = -1;
        for (int i = 0; i < N; i++) cin >> p[i] >> w[i];

        ll M; cin >> M;
        ll ans = 0;
        for (int i = 0; i < M; i++) {
            ll a; cin >> a; ans += f(0, a);
        }
        cout << ans << '\n';
    }
}

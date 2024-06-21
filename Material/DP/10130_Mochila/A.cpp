#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1001; 
const int maxg = 31;

ll dp[maxn][maxg];
ll p[maxn];
ll w[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        for (int i = 0; i < maxn; i++) for(int j = 0; j < maxg; j++) dp[i][j] = 0;
        ll N; cin >> N; 
        for (int i = 0; i < N; i++) cin >> p[i] >> w[i];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j + w[i] < maxg; j++) dp[i+1][j+w[i]] = max(dp[i+1][j+w[i]], dp[i][j] + p[i]);
            for (int j = 0; j < maxg; j++) dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
        }
        /*
        for (int i = 0; i < maxg; i++) cout << dp[N][i] << ' ' ;
        cout << endl;
        */
        ll M; cin >> M;
        ll ans = 0;
        for (int i = 0; i < M; i++) {
            ll a; cin >> a; ans += dp[N][a];
        }
        cout << ans << '\n';
    }
}

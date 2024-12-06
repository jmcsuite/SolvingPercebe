#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const long long mod = 998244353;

const int maxn = 2e5 + 2;
const int maxk = 10 + 2;

ll dp[maxn][maxk];

ll N, K;

void f() {
    for (int i = 0; i <= N; i++) dp[i][0] = 1;
    for (int i = 1; i <= N; i++) {
        for (int k = 1; k <= K; k++) {
            dp[i][k] = dp[i-1][k-1];
            if (k <= 2) continue;
            if (i <= 1) continue;
            dp[i][k] = (dp[i][k] - dp[i-2][k-1])%mod;
            if (i <= 2) continue;
            dp[i][k] = (dp[i][k] + dp[i-3][k-1])%mod;
        }

        ll sk = dp[i-1][K];
        if (i > 1) sk = (sk - dp[i-2][K]) % mod;
        if (i > 2) sk = (sk + dp[i-3][K]) % mod;
        dp[i][K] = (dp[i][K] + sk) % mod;

        for (int k = 1; k <= K; k++) dp[i][k] = (dp[i][k] + dp[i-1][k]) % mod;
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> K;
    f();
    ll ans = (dp[N][K] - dp[N-1][K]) % mod;
    ans = (ans + mod) % mod;
    cout << ans << '\n';
}

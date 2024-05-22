#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 500;

ll dp[maxn][maxn+1];
ll sec[maxn][maxn+1];

void init_sec() {
    for ( int i = 0; i < maxn; i++) {
        for( int j = 0; j <= maxn; j++) sec[i][j] = 1e9;
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, K;
    cin >> N >> K;
    string s; cin >> s;

    for (int i = 0; i < N; i++) {
        for(int j = 0; j <= N; j++) dp[i][j] = 1e9;
    }
    init_sec();

    if (K%2) for(int i=0; i < N; i++) dp[i][1] = 0;
    else for(int i=0; i < N; i++) dp[i][0] = 0;

    K /= 2;

    for (ll k = 0; k < K; k++) {
        for (ll i = N-1; i >= 0; i--) {
            for (ll r = 0; r <= N; r++) {
                if (i + r + 1 <= N) {
                    dp[i][r+1] = min(dp[i][r+1], dp[i][r]);
                }
                if (i-1 >= 0) {
                    dp[i-1][r+1] = min(dp[i-1][r+1], dp[i][r]);
                }
                
                if (i-1 >= 0 && i+r+1 <= N) {
                    char aa = s[i-1];
                    char bb = s[i+r];
                    ll c = (aa == bb ? 0 : 1);
                    sec[i-1][r+2] = min(sec[i-1][r+2], c + dp[i][r]);
                }
            }
        }

        swap(dp,sec);
        init_sec();
    }

    ll ans = 1e9;
    for (int i = 0; i < N; i++) {
        for (int r = 0; r+i <= N; r++) {
            ans = min(ans, dp[i][r]);
        }
    }

    cout << ans << '\n';
}

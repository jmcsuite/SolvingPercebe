#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e6+1;
const int maxm = 1415;

bool dp[maxm][maxm];

void calc() {
    for (int i = 2; i < maxm; i++) {
        for (int j = i; j < maxm; j+=i) {
            for( int k = i; k < maxm; k+=i) {
                dp[j][k] = true;
            }
        }
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    calc();
    ll T; cin >> T;
    while (T--) {
        ll N, M; cin >> N >> M;
        ll ans = 0;
        for (int i = 1; i*i < N; i++) {
            for (int j = 1; j*j < M; j++) {
                if (dp[i][j]) continue;
                ll d = i+j;
                ans += min((N/(i*d)), M/(j*d));
            }
        }
        cout << ans << '\n';
    }
}


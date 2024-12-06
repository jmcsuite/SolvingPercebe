#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const int maxn = 800;

ll vl[maxn];
ll dp[maxn][maxn];

ll sol[maxn];
ll N;

ll inf = 1e5;

void fill() {
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) dp[i][j] = inf;
    for (int i = 0; i < N; i++) for (int j = i-1; j >= 0; j--) dp[i][j] = 0;

    for (int k = 2; k <= N; k++) {
        for (int i = 0, j = i + k - 1; j < N; j++, i++) {
            ll delta = i - vl[i];
            if (delta < 0 || (delta%2)) continue;
            for (int r = j; r > i; r--) {
                ll nd = dp[i+1][r-1];
                if (nd > delta) continue;

                ll ans = delta;
                if (r+1 < N) {
                    ans = max(delta, dp[r+1][j] - (r - i + 1));
                }
                dp[i][j] = min(dp[i][j], ans);
            }
        }
    }
}

void f2() {
    for (int i = 0; i < N; i++) sol[i] = 0;
    for (int i = 1; i < N; i++) {
        sol[i] = ((dp[0][i] == 0) ? i+1 : sol[i-1]);
        for (int j = 0; j < i; j++) {
            if (sol[j] >= dp[j+1][i]) sol[i] = max(sol[i], sol[j] + i - j);
        }
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> N;
        for (int i = 0; i < N; i++) cin >> vl[i];
        for (int i = 0; i < N; i++) vl[i]--;

        fill();
        f2();
        cout << sol[N-1]/2 << '\n';
    }
}

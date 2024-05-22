#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll T, N, K;
const int maxn = 3e5;
const int maxk = 11;

ll dp[maxn][maxk];
ll vl[maxn];

ll f(ll i, ll k) {
    if (i == N)
        return 0;
    if (dp[i][k]) return dp[i][k];

    ll ans = 1e15;
    ll m = vl[i];
    for (int j = 0; j + i < N && j <= k; j++) {
        m = min(vl[i+j], m);
        ans = min(ans, m*(j+1) + f(i+j+1, k-j));
    }
    return dp[i][k] = ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while(T--) {
        cin >> N >> K;
        for (int i = 0; i < N; i++) cin >> vl[i];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= K; j++) dp[i][j] = 0;
        }
        cout << f(0, K) << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 21;

ll dp[maxn][maxn];
ll N; 
ll vl[maxn];

ll f(ll x, ll c) {
    if (x == N-1 && c == N-2) return vl[x];
    if (x == N-1 && c != N-2) return 1e9;
    if (dp[x][c] != -1) return dp[x][c];
    ll ans = 1e9;

    if (c <= N-3) {
        ans = min(ans, vl[x] + f(x+1, c+1));
        ans = min(ans, vl[x] * f(x+1, c+1));
    }
    if (c >= x-1) {
        ans = min(ans, vl[x] * 10 + f(x+1, c));
    }
    return dp[x][c] = ans;
}


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> N;
        string a; cin >> a;
        for (int i = 0; i < N; i++) vl[i] = a[i] - '0';
        memset(dp, -1, sizeof dp);
        cout << f(0,0) << '\n';
    }
}

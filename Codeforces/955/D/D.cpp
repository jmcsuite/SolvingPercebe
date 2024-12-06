#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 500;
ll vl[maxn][maxn];

ll s[maxn][maxn];

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b%a, a);
}

void solve() {
    ll N, M, K; cin >> N >> M >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cin >> vl[i][j];
    }

    for (int i = 0; i < N; i++) {
        string str; cin >> str;
        for (int j = 0; j < M; j++) s[i][j] = (str[j] == '1' ? 1 : -1);
    }

    ll sa = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) sa = sa + s[i][j] * vl[i][j];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (i > 0) s[i][j] += s[i-1][j];
            if (j > 0) s[i][j] += s[i][j-1];
            if (i > 0 && j > 0) s[i][j] -= s[i-1][j-1];
        }
    }

    if (sa < 0) sa *= -1;
    if (sa == 0) {
        cout << "YES\n";
        return;
    }

    ll gg = 0;
    for (int i = K-1; i < N; i++) {
        for (int j = K-1; j < M; j++) {
            ll cc = s[i][j];
            if (i >= K) cc -= s[i-K][j];
            if (j >= K) cc -= s[i][j-K];
            if (i >= K && j >= K) cc += s[i-K][j-K];
            if (cc < 0) cc *= -1;
            if (cc == 0) continue;
            if (gg == 0) gg = cc;
            gg = gcd(cc, gg);
        }
    }
    if (gg == 0) {
        cout << "NO\n";
        return;
    }
    if (sa % gg == 0) {
        cout << "YES\n";
        return;
    }
    cout << "NO\n";
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}


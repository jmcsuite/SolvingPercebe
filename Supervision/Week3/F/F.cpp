#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5 + 5;
const int maxc = 'Z' - 'A' + 1;

ll t[2][maxn][maxc];
ll sz[2];
ll cc[2][maxc];
bool term[maxn];

void add(const int k, string& s) {
    ll n = 0;
    for (const char c: s) {
        if (t[k][n][c-'a']) {
            n = t[k][n][c-'a'];
        }
        else {
            if (n == 0) cc[k][c-'a']--;
            cc[k][c-'a']++;
            n = t[k][n][c-'a'] = ++sz[k];
        }
    }
}

void clear() {
    for (int k=0; k<2; k++) {
        for (int i=0; i<sz[k]; i++) {
            for (int c=0; c<maxc; c++) t[k][i][c] = 0;
        }
        sz[k]=0;
        for (int c=0; c<maxc; c++) cc[k][c] = 0;
    }
}

ll N,M;
void solve() {
    clear();
    for (int i=0; i<N; i++) {
        string s; cin>>s;
        add(0,s);
    }
    for (int i=0; i<M; i++) {
        string s; cin>>s;
        reverse(s.begin(), s.end());
        add(1,s);
    }

    ll ans = 0;
    for (int i=1; i <= sz[0]; i++) {
        ans += sz[1];
        for (int c=0; c<maxc; c++) {
            if (t[0][i][c]) ans -= cc[1][c];
        }
    }
    cout << ans << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin>>N>>M, N || M) solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll N,M;
vector<vector<int>> vis;
vector<vector<int>> vis2;

void DFS(ll x, ll y) {
    if (x >= N || y >= M) return;
    if (vis[x][y]) return;
    vis[x][y] = 1;
    DFS(x+1, y);
    DFS(x, y+1);
}

void DFS2(ll x, ll y) {
    if (x < 0 || y < 0) return;
    if (vis2[x][y]) return;
    vis2[x][y] = 1;
    DFS2(x-1, y);
    DFS2(x, y-1);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N >> M;
    vis.resize(N);
    vis2.resize(N);
    for (int i = 0; i < N; i++) vis[i].resize(M);
    for (int i = 0; i < N; i++) vis2[i].resize(M);
    for (int i = 0; i < N; i++) {
        string s; cin >> s;
        for (int j = 0; j < M; j++) vis[i][j] = (s[j] == '#' ? 2 : 0);
        for (int j = 0; j < M; j++) vis2[i][j] = (s[j] == '#' ? 2 : 0);
    }
    DFS(0,0);
    DFS2(N-1, M-1);

    if (vis[N-1][M-1] == 0) {
        cout << 0 << '\n';
        return 0;
    }

    ll ans = 2;
    for (int i = 1; i < N; i++) {
        ll x = i; ll y = 0; ll cc = 0; 
        while(x >= 0 && y < M) {
            if (vis[x][y] == 1 && vis2[x][y] == 1) cc++;
            x--; y++;
        }
        ans = min(cc, ans);
    }

    for (int j = 1; j < M-1; j++) {
        ll x = N-1; ll y = j; ll cc = 0;
        while(x >= 0 && y < M) {
            if (vis[x][y] == 1 && vis2[x][y] == 1) cc++;
            x--; y++;
        }
        ans = min(cc, ans);
    }

    cout << ans << '\n';
    return 0;
}

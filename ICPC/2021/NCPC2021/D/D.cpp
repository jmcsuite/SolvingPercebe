#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

ll dx[4] = {-1, 0, 1, 0}; // N, E, S, W
ll dy[4] = {0, 1, 0, -1};


const int maxn = 1e3;
ll mat[maxn][maxn];
ll dis[maxn][maxn];
ll ans[maxn][maxn];

void bfs(ll x, ll y) {
    queue<pll> q; 
    q.push({x,y});
    dis[x][y] = 0;
    while (!q.empty()) {
        pll v = q.front();
        q.pop();
        for (int k = 0; k < 4; k++) {
            ll nx = v.first + dx[k];
            ll ny = v.second + dy[k];
            if (mat[nx][ny] == -1) continue;
            if (dis[nx][ny] != -1) continue;
            q.push({nx,ny});
            dis[nx][ny] = dis[v.first][v.second] + 1;
        }
    }
}

void gbfs(ll x, ll y, ll s, vector<ll>& id) {
    queue<pll> q;
    q.push({x,y});
    while (!q.empty()) {
        pll v = q.front();
        q.pop();
        if (dis[v.first][v.second] == s) return;
        for (int k = 0; k < 4; k++) {
            if (k == id[dis[v.first][v.second]]) continue;
            ll nx = v.first + dx[k];
            ll ny = v.second + dy[k];
            if (dis[nx][ny] != dis[v.first][v.second] + 1) continue;
            if (mat[nx][ny] == -1) continue;
            if (ans[nx][ny]) continue;
            ans[nx][ny] = 1;
            q.push({nx,ny});
        }
    }
}


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll M, N; cin >> M >> N;
    ll inix, iniy;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            char c; cin >> c;
            if (c == '#') mat[i][j] = -1;
            if (c == 'S') {
                inix = i;
                iniy = j;
            }
        }
    }
    string s; cin >> s;
    vector<ll> id(s.size());
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == 'N') id[i] = 0;
        else if (s[i] == 'S') id[i] = 2;
        else if (s[i] == 'W') id[i] = 3;
        else id[i] = 1;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) dis[i][j] = -1;
    }

    bfs(inix, iniy);
    gbfs(inix, iniy, s.size(), id);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (mat[i][j] == -1) {
                cout << '#';
                continue;
            }
            if (i == inix && j == iniy) {
                cout << 'S';
                continue;
            }
            if (dis[i][j] == (int)s.size() && ans[i][j]) cout << '!';
            else cout << '.';
        }
        cout << '\n';
    }
}

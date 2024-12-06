#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 5e2;
ll vl[maxn][maxn];

vpll g[2];
vpll ans;

ll dx[4] = {0,1,0,-1};
ll dy[4] = {1,0,-1,0};

ll N,M;
bool check(ll x, ll y) {
    if (x < 0 || x >= N) return false;
    if (y < 0 || y >= M) return false;
    return true;
}

void DFS(ll x, ll y, ll p) {
    if (vl[x][y] == 0) return;
    g[p].push_back({x,y});
    ll num = vl[x][y];
    vl[x][y] = 0;
    p = (p+1)%2;

    for (int k = 0; k < 4; k++) {
        ll nx = x + dx[k];
        ll ny = y + dy[k];
        if (!check(nx, ny)) continue;
        if (vl[nx][ny] != num) continue;
        DFS(nx,ny,p);
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;
    for (int i=0; i<N; i++) for(int j=0; j<M; j++) cin >> vl[i][j];
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            g[0].clear();
            g[1].clear();
            DFS(i,j,0); 
            if (g[0].size() > g[1].size()) swap(g[0], g[1]);
            for (pll x: g[0]) ans.push_back(x);
        }
    }

    if (ans.size() == 0) {
        cout << "0 0\n";
        return 0;
    }
    cout << "1 " << ans.size() << '\n';
    for (pll x : ans) {
        cout << ++x.first << ' ' << ++x.second << ' ' << 1 << '\n';
    }
}

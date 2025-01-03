#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 150; 
namespace hungarian {

bool vis[2][maxn];
ll edge[maxn][maxn];
ll vl[2][maxn];
ll up[2][maxn];
ll match[2][maxn];

pll minEdge[maxn];
ll N;

void dfs(ll a, ll x, ll p) {
    if (vis[a][x]) return;
    vis[a][x] = true;
    up[a][x] = p;

    if (a==1) {
        if (match[a][x]==-1) return;
        dfs(0, match[a][x], x);
        return;
    }

    for (int i=0; i<N; i++) {
        ll c = edge[x][i];
        if (vl[1][i] + vl[0][x] != c) continue;
        dfs(1,i,x);
    }
    return;
}

void setup() {
    for (int i=0; i<N; i++) match[0][i] = -1;
    for (int i=0; i<N; i++) match[1][i] = -1;
    for (int i=0; i<N; i++) vl[0][i] = 0;
    for (int i=0; i<N; i++) vl[1][i] = 0;
}

void updatemin(ll x) {
    minEdge[x] = {1e9, -1};
    for (int j=0; j<N; j++) {
        if (vis[1][j]) continue;
        minEdge[x] = min(minEdge[x], {edge[x][j]-vl[1][j], j});
    }
}

pll findmin() {
    pll ans = {1e9, -1};
    ll x = -1; for (int i=0; i<N; i++) {
        if (!vis[0][i]) continue;
        if (ans.first <= minEdge[i].first - vl[0][i]) continue;
        ans = minEdge[i]; ans.first-=vl[0][i];
        x=i;
    }
    return {x,ans.second};
}

void rundfs(ll x) {
    for (int i=0; i<N; i++) vis[0][i] = 0;
    for (int i=0; i<N; i++) vis[1][i] = 0;

    for (int i=0; i<N; i++) {
        if (match[0][i] != -1) continue;
        dfs(0,i,-1);
        break;
    }

    for (int i=0; i<N; i++) {
        if (!vis[0][i]) minEdge[i] = {1e9, -1};
        else updatemin(i);
    }
}

void invert(ll x, ll u) {
    ll p = up[1][u];
    while (p != x) {
        match[1][u] = p;
        match[0][p] = u;
        u = up[0][p];
        p = up[1][u];
    }
    match[1][u] = p;
    match[0][p] = u;
    return;
}

void hall(ll x) {
    rundfs(x);
    for (int i=0; i<N; i++) {
        if (!vis[1][i]) continue;
        if (match[1][i] != -1) continue;
        invert(x,i);
        return;
    }
    while (1) {
        pll e = findmin();
        if (vis[1][e.second]) {
            updatemin(e.first);
            continue;
        }
        ll c = edge[e.first][e.second] - vl[0][e.first] - vl[1][e.second];
        for (int i=0; i<N; i++) {
            if (vis[1][i]) vl[1][i] -= c;
            if (vis[0][i]) vl[0][i] += c;
        }
        assert(c >= 0);
        up[1][e.second] = e.first;
        vis[1][e.second] = true;
        if (match[1][e.second] != -1) {
            up[0][match[1][e.second]] = e.second;
            vis[0][match[1][e.second]] = true;
            updatemin(e.first);
            updatemin(match[1][e.second]);
            continue;
        }
        invert(x, e.second);
        return;
    }
}

ll mincost(ll n) {
    N = n;
    setup(); 
    while (1) {
        bool perfect = true;
        for (int i=0; i<N; i++) {
            if (match[0][i] == -1) {
                perfect = false;
                hall(i);
                break;
            }
        }
        if (perfect) break;
    }
    ll ans = 0;
    for (int i=0; i<N; i++) ans += vl[0][i] + vl[1][i];
    return ans;
}
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (int i=0; i<N; i++) {
        ll s = 0;
        for (int j=0; j<N; j++) cin >> hungarian::edge[i][j];
        for (int j=0; j<N; j++) s+=hungarian::edge[i][j];
        for (int j=0; j<N; j++) hungarian::edge[i][j] = s - hungarian::edge[i][j];
    }
    cout << hungarian::mincost(N) << '\n';
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 2000;
const int maxm = 50000;


struct Edge{
    int u,v; 
    Edge() : u(0), v(0) {}
    Edge(ll a, ll b) : u(a), v(b) {}
};

Edge e[maxm];
vll adj[2][maxn];
ll bridge[maxm];
bool vis[maxn];

void DFS(ll x, vll vadj[maxn]) {
    vis[x]=1;
    for(ll y: vadj[x]) {
        int v = e[y].u;
        if (v == x) v = e[y].v;
        if (vis[v]) continue;
        bridge[y]=1;
        DFS(v, vadj);
    }
}

void F(ll x,ll ne, vll vadj[maxn]) {
    vis[x]=1;
    for(ll y: vadj[x]) {
        if(y==ne) continue;
        if(vis[e[y].v]) continue;
        F(e[y].v, ne, vadj);
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M; 
    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        ll u,v; cin >> u >> v; 
        u--; v--;
        e[i].u=u; e[i].v=v;
        adj[0][u].push_back(i);
        adj[1][v].push_back(i);
    }

    DFS(0, adj[0]);
    for(int i = 0; i < N; i++) vis[i]=false;
    DFS(0, adj[1]);
    for(int i = 0; i < N; i++) vis[i]=false;

    ll ans = 0;
    for (int i = 0; i < M; i++) {
        if (bridge[i] == 0) continue;
        for(int i = 0; i < N; i++) vis[i]=false;
        F(e[i].u, i, adj[0]);
        bridge[i] = (vis[e[i].v] ? 0 : 1);
        if (bridge[i]) ans++;
    }
    cout << ans << '\n';
    for (int i = 0; i < M; i++) {
        if(bridge[i]) cout << e[i].u+1 << ' ' << e[i].v+1 << '\n';
    }
}

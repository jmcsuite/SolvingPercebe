#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 1e5;

ll ans[maxn];
ll sz[maxn];
map<int,int> mp[maxn];
vector<ll> vadj[maxn];

ll f(ll x, ll k) {
    if (mp[k].find(x) == mp[k].end()) return x;
    if (mp[k][x] == x) return x;
    return mp[k][x] = f(mp[k][x], k);
}

void un(ll a, ll b, ll k) {
    ll pa = f(a,k);
    ll pb = f(b,k);
    if (pa == pb) return;
    sz[k]--;
    mp[k][pa] = pb;
}

void DFS(ll x, ll p) {
    for (ll y : vadj[x]) {
        if (y == p) continue;
        DFS(y,x);
    }

    for (ll y: vadj[x]) {
        if (y == p) continue;
        if (mp[y].size() > mp[x].size()) {
            swap(mp[y], mp[x]);
            swap(sz[y], sz[x]);
        }
        for(pll e : mp[y]) {
            un(e.first, e.second, x);
        }
    }
    ans[x] = sz[x];
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M; cin >> N >> M;
    for (int i = 1; i < N; i++) {
        ll b; cin >> b; b--;
        vadj[i].push_back(b);
        vadj[b].push_back(i);
    }
    for (int i = 0; i < N; i++) sz[i] = M;
    for (int i = 0; i < N; i++) {
        ll a,b; cin >> a >> b;
        un(a,b,i);
    }
    DFS(0,0);
    for (int i = 0; i < N; i++) cout << ans[i] << '\n';
}

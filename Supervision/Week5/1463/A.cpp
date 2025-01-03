#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 50000;
bool vis[maxn];
vpll vadj[maxn];
ll vl[maxn];


pll farthest(ll x, ll p) {
    pll f(0,x);
    for (pll y: vadj[x]) {
        if (y.first == p) continue;
        pll sum = farthest(y.first, x);
        sum.first += y.second;
        f = max(f, sum);
    }
    f.first += vl[x];
    return f;
}


void dfs(ll x, ll p) {
    vis[x] = 1;
    for (pll y: vadj[x]) {
        if (y.first == p) continue;
        dfs(y.first, x);
    }
}

pll diameter(ll x) {
    dfs(x, x);
    ll y = farthest(x,x).second;
    return farthest(y,y);
}

vll gg;
bool getans(ll x, ll y, ll p) {
    if (x == y) {
        gg.push_back(x);
        return true;
    }
    bool se = false;
    for (pll e : vadj[x]) {
        if (e.first == p) continue;
        se |= getans(e.first, y, x);
    }
    if (se) gg.push_back(x);
    return se;
}

int main() {
    ios::sync_with_stdio(0);
    ll N,K; cin>>N>>K; 
    for (int i=0; i<N; i++) cin >> vl[i];
    while (K--) {
        ll a, b, c; 
        cin >> a >> b >> c;
        --a; --b;
        vadj[a].push_back({b,c});
        vadj[b].push_back({a,c});
    }

    pll ans = {0,0};
    for (int i = 0; i<N; i++) {
        if (!vis[i]) ans = max(ans, diameter(i));
    }
    pll y = farthest(ans.second, ans.second);
    cout << ans.first << '\n';

    getans(ans.second,y.second,ans.second);
    cout << gg.size() << '\n';
    for (int i=0; i<(int)gg.size(); i++) {
        cout << gg[i]+1 << (i+1 == (int)gg.size() ? '\n' : ' ');
    }
}

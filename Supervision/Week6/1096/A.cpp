#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
const int maxn = 2001;

vll vadj[maxn]; 
ll vis[maxn];


vll sol(ll x,ll y, ll T) {
    for (int i=0; i<maxn; i++) vis[i]=0;
    vis[x] = x; vis[y] = y;
    queue<ll> q; 
    q.push(x);
    if (x != y) q.push(y);
    while (!q.empty()) {
        ll u = q.front(); 
        q.pop(); 
        for (ll v: vadj[u]) {
            if (vis[v]) continue;
            vis[v]=u;
            q.push(v);
        }
    }

    if (vis[T] == 0) return {};

    vll ans;
    ll u = T; 
    while (vis[u] != u) {
        ans.push_back(u);
        u = vis[u];
    }
    ans.push_back(u);
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    map<pll,ll> mp;
    for (int i=0; i<N; i++) {
        ll a,b; cin>>a>>b;
        vadj[a].push_back(b);
        mp[{a,b}] = i+1;
    }
    ll T, a, b; cin>>T>>a>>b;
    auto va = sol(a,b,T);
    if (va.empty()) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    cout << (va.size()-1) << '\n';
    for (int i=0; i<(int)va.size() - 1; i++) {
        cout << mp[{va[i], va[i+1]}] << '\n';
    }
}

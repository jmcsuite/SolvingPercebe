#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 2e5;
vll vadj[maxn];
ll vis[maxn];
ll cc[maxn];
ll depth[maxn];

void dp(ll x, ll p) {
    depth[x] = depth[p]+1;
    for (ll y: vadj[x]) {
        if (y == p) continue;
        dp(y,x);
    }
}

void visit(ll x) {
    if (vis[x]) return;
    vis[x] = 1;
    for (ll y: vadj[x]) visit(y);
}

void solve() {
    ll n; cin>>n;
    for (int i=0; i<n; i++) {
        cc[i] = 0;
        vis[i] = false;
        vadj[i].clear();
        depth[i] = 0;
    }

    for (int i=1; i<n; i++) {
        ll a,b; cin>>a>>b;
        a--; b--;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
        cc[a]++;
        cc[b]++;
    }
    depth[0] = 0;

    dp(0,0);
    ll x = 0; 
    ll c = cc[0];
    ll d = depth[0];

    for (int i=0; i<n; i++) {
        if (cc[i] < c) continue;
        if (cc[i] > c || depth[i] > d) {
            x = i;
            c = cc[i];
            d = depth[i];
            continue;
        }
    }

    for (ll y: vadj[x]) cc[y]--;
    vis[x] = 1;
    x = c = d = 0;
    c = -1;
    for (int i=0; i<n; i++) {
        if (vis[i]) continue;
        if (cc[i] < c) continue;
        if (cc[i] > c || depth[i] > d) {
            x = i;
            c = cc[i];
            d = depth[i];
            continue;
        }
    }
    vis[x] = 1;
    
    ll ans = 0;
    for (int i=0; i<n; i++) {
        if (vis[i]) continue;
        ans++;
        visit(i);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}

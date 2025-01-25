#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 3e5 + 7;

ll sz[maxn];
ll depth[maxn];
ll freq[maxn];
ll sum[maxn];
vll vadj[maxn];
ll ans;

void clear(ll n) {
    for (int i=0; i<=n; i++) vadj[i].clear();
    for (int i=0; i<=n+2; i++) sz[i] = depth[i] = freq[i] = sum[i] = 0;
    ans = 0;
}

void pre(ll x, ll p) {
    depth[x] = depth[p] + 1;
    freq[depth[x]]++;
    sz[x] = 1;
    for (ll y : vadj[x]) {
        if (y == p) continue;
        pre(y,x);
        sz[x] += sz[y];
    }
}

void calc(ll x, ll p) {
    ll thn = sum[depth[x]+1] + freq[depth[x]] - sz[x];
    freq[depth[x]]--;
    ans += thn * 2ll * depth[x];
    
    ll prev = 0;
    for (ll y: vadj[x]) {
        if (y == p) continue;
        ll nn = (prev * sz[y]);
        ll cant = 2*depth[x] + 1;
        ans -= nn*cant;
        prev += sz[y];
        calc(y,x);
    }
}

void solve() {
    ll n; cin>>n;
    clear(n);
    for (int i=1; i<n; i++) {
        ll a,b; cin>>a>>b;
        --a; --b;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }

    pre(0,0);
    sum[n+2] = freq[n+2];
    for (int i=n+1; i>=0; i--) {
        sum[i] = freq[i] + sum[i+1];
    }
    calc(0,0);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll t; cin>>t;
    while(t--) solve();
}

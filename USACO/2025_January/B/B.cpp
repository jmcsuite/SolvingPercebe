#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 2e5 + 10;
ll vl[maxn];
ll c[maxn];
ll rr[maxn];
ll sz[maxn];
vector<pll> op[maxn]; 
vector<pll> edges[maxn];
ll ans=0;

ll ff(ll x) {
    if (vl[x] == x) return x;
    return ff(vl[x]);
}


pll un(ll a, ll b) {
    // vl[first] = second;
    ll pa = ff(a);
    ll pb = ff(b);
    if (pa == pb) return {pa,pb};
    if (rr[pa] < rr[pb]) {
        sz[pb] += sz[pa];
        vl[pa] = pb;
        return {pa, pb};
    }
    sz[pa] += sz[pb];
    vl[pb] = pa;
    if (rr[pb] == rr[pa]) rr[pa]++;
    return {pb, pa};
}

ll func(ll x) {
    return ((x) * (x-1) ) / 2;
}

void update_black(ll x) {
    while (vl[x] != x) {
        sz[x]--;
        x = vl[x];
    }
    ans -= func(sz[x]);
    sz[x]--;
    ans += func(sz[x]);
}

void undo(ll pa, ll pb) {
    if (pa == pb) return;
    ans -= func(sz[pb]);
    sz[pb] -= sz[pa];
    vl[pa] = pa;
    ans += func(sz[pb]) + func(sz[pa]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n,m; cin>>n>>m;

    for (int i=1; i<=n; i++) {
        vl[i] = i;
        sz[i] = 1;
    }

    string s; cin>>s;
    for (int i=0; i<(int)s.size(); i++) {
        c[i+1] = s[i]-'0';
    }

    for (int i=0; i<m; i++) {
        ll a,b; cin>>a>>b;
        if (c[a] == 1 && c[b] == 1) {
            un(a,b);
            continue;
        }
        if (c[a] == 0) {
            edges[a].push_back({a,b});
        }
        if (c[b] == 0) {
            edges[b].push_back({b,a});
        }
    }

    for (ll i=n; i>0; i--) {
        if (c[i] == 1) continue;
        for (pll p: edges[i]) {
            if (p.second < i && c[p.second] == 0) continue;
            op[i].push_back(un(p.first, p.second));
        }
    }

    for (int i=1; i<=n; i++) {
        if (vl[i] != i) continue;
        ans += func(sz[i]);
    }

    for (int i=0; i<n; i++) {
        cout << ans << '\n';
        ll x = i+1;
        if (s[i] == '1') {
            update_black(x);
            continue;
        }
        reverse(op[x].begin(), op[x].end());
        for (pll p: op[x]) {
            undo(p.first, p.second);
        }
    }
}

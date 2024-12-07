#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;

const int maxn=1e5;
vll vadj[maxn];
ll N;

namespace lca {
    const int maxPow=20;
    ll vl[maxn];
    pll depth[2*maxn];
    pll dp[2*maxn][maxPow];
    ll t,d;
    void build(int x, int p) {
        vl[x]=t;
        depth[t++]={d,x};
        for(ll y: vadj[x]) {
            if (y==p) continue;
            ++d;
            build(y,x);
            depth[t++]={d,x};
        }
        --d;
    }

    void buildPow() {
        for (int i=0; i<(2*N-1); i++) dp[i][0]=depth[i];
        for (int j=1; j<maxPow; j++) {
            for (int i=0; i<(2*N-1); i++) {
                dp[i][j] = dp[i][j-1];
                int k = i+(1<<(j-1));
                if (k >= 2*N-1) continue;
                dp[i][j]=min(dp[i][j], dp[k][j-1]);
            }
        }
    }

    ll query(ll _a, ll _b) {
        ll a = min(vl[_a], vl[_b]);
        ll b = max(vl[_a], vl[_b]);
        ll dis = b-a+1;
        ll lz = 63-__builtin_clzll(dis);
        ll k = b-(1<<lz)+1;
        pll ans = min(dp[a][lz], dp[k][lz]);
        return ans.second;
    }

    void preprocess(ll x) {
        t=d=0;
        build(x,x);
        buildPow();
    }
}

namespace centroid {
    ll sz[maxn];
    ll vis[maxn];
    ll p[maxn];
    ll root;
    ll ans[maxn];

    void calc(ll x, ll p) {
        sz[x]=1;
        for (ll y: vadj[x]) {
            if (y == p || vis[y]) continue;
            calc(y,x);
            sz[x] += sz[y];
        }
    }

    ll find(ll x, ll p, ll n) {
        for (ll y: vadj[x]) {
            if (y == p || vis[y]) continue;
            if (sz[y] > n) return find(y,x,n);
        }
        return x;
    }

    void build(int c) {
        vis[c]=1;
        for (ll y: vadj[c]) {
            if (vis[y]) continue;
            calc(y,y);
            ll c2 = find(y,y,sz[y]/2);
            p[c2]=c;
            build(c2);
        }
    }

    //call this;
    void init() {
        calc(0,0);
        root = find(0,0,sz[0]/2);
        p[root] = root;
        build(root);
        // specific to problem
        for (int i=0; i<maxn; i++) ans[i]=1e7;
    }

    void update(ll x) {
        ll u = x;
        while (u != root) {
            ans[u] = min(ans[u], lca::depth[lca::vl[x]].first + lca::depth[lca::vl[u]].first - 2*lca::depth[lca::vl[lca::query(x,u)]].first);
            u = p[u];
        }
        ans[u] = min(ans[u], lca::depth[lca::vl[x]].first + lca::depth[lca::vl[u]].first - 2*lca::depth[lca::vl[lca::query(x,u)]].first);
    }

    ll query(ll x) {
        ll u = x;
        ll a = 1e7;
        while (u != root) {
            a = min(a, ans[u] + lca::depth[lca::vl[u]].first + lca::depth[lca::vl[x]].first - 2*lca::depth[lca::vl[lca::query(x,u)]].first);
            u = p[u];
        }
        a = min(a, ans[u] + lca::depth[lca::vl[u]].first + lca::depth[lca::vl[x]].first - 2*lca::depth[lca::vl[lca::query(x,u)]].first);
        return a;
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll Q; cin>>N>>Q;
    for (int i=1; i<N; i++) {
        ll a,b; cin >> a >> b;
        --a; --b;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }

    lca::preprocess(0);
    centroid::init();
    centroid::update(0);

    while (Q--) {
        ll t, x; cin>>t>>x; --x;
        if (t == 2) cout << centroid::query(x) << '\n';
        else centroid::update(x);
    }
}


#include <bits/stdc++.h>
using namespace std;
using ll = int;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=1e5;
vll vadj[maxn];
long long vdis[maxn];
ll N;

//namespace lca {
    const int maxPow=20;
    ll vl[maxn];
    pll depth[2*maxn];
    pll dp[2*maxn][maxPow];
    ll t,d;

    void build(int x, int p) {
        vl[x]=t;
        depth[t++]={d,x};
        for (ll y: vadj[x]) {
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
                dp[i][j] = min(dp[i][j], dp[k][j-1]);
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
//}

//namespace centroid {
    ll sz[maxn];
    ll vis[maxn];
    ll p[maxn];
    ll root;
    vector<long long> st[maxn];
    vector<long long> sub[maxn];
    
    void calc(ll x, ll u) {
        sz[x]=1;
        for (ll y: vadj[x]) {
            if (y==u || vis[y]) continue;
            calc(y,x);
            sz[x] += sz[y];
        }
    }

    ll find(ll x, ll u, ll n) {
        for (ll y: vadj[x]) {
            if (y == u || vis[y]) continue;
            if (sz[y] > n) return find(y,x,n);
        }
        return x;
    }

    /*
    void addSt(ll x, ll u, ll c) {
        st[c].push_back(vdis[c] + vdis[x] - 2*vdis[lca::query(x,c)]);
        for (ll y: vadj[x]) {
            if (y == u || vis[y]) continue;
            addSt(y,x,c);
        }
    }
    */

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

    void ansBuild() {
        for (ll i=0; i<N; i++) {
            ll u=i;
            st[u].push_back(0);
            while (u != root) {
                u = p[u];
                st[u].push_back(vdis[i] + vdis[u] - 2*vdis[query(u,i)]);
            }
        }
        for (ll i=0; i<N; i++) sort(st[i].begin(), st[i].end());
    }

    void subBuild() {
        for (int i=0; i<N; i++) {
            int u=i;
            while (u != root) {
                sub[u].push_back(vdis[i] + vdis[p[u]] - 2*vdis[query(p[u], i)]);
                u = p[u];
            }
        }

        for (int i=0; i<N; i++) sort(sub[i].begin(), sub[i].end());
    }



    // call this;
    void cinit() {
        calc(0,0);
        root = find(0,0,sz[0]/2);
        p[root] = root;
        build(root);
        ansBuild();
        subBuild();
    }

    ll search(ll x, long long l) {
        ll ans = -1; 
        ll dis = st[x].size();
        while (dis) {
            if (ans + dis < (int)st[x].size() && st[x][ans+dis] <= l) ans += dis;
            else dis/=2;
        }
        return ans+1;
    }

    ll subsearch(ll x, long long l) {
        ll ans = -1; 
        ll dis = sub[x].size();
        while (dis) {
            if (ans + dis < (int)sub[x].size() && sub[x][ans+dis] <= l) ans += dis;
            else dis/=2;
        }
        return ans+1;
    }

    ll solve(ll x, long long l) {
        ll u = x;
        ll ans = search(u, l);
        ll prev = x;
        while (u != root) {
            u = p[u];
            long long dxu = vdis[x] + vdis[u] - 2*vdis[query(x,u)];
            ans = ans + search(u, l-dxu) - subsearch(prev, l-dxu);
            prev = u;
        }
        return ans;
    }
//}

vector<pair<int,long long>> disAdj[maxn];
void init(ll x, ll u) {
    for (pair<int,long long> y: disAdj[x]) {
        if (y.first == u) continue;
        vdis[y.first] = vdis[x]+y.second;
        init(y.first, x);
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll Q; cin >> N >> Q;
    for (int i=1; i<N; i++) {
        ll a,b; long long c; cin >> a >> b >> c; --a; --b;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
        disAdj[a].push_back({b,c});
        disAdj[b].push_back({a,c});
    }

    init(0,0);
    preprocess(0);
    cinit();

    while (Q--) {
        long long l;
        ll a; cin >> a >> l; --a;
        cout << solve(a, l) << '\n';
    }
}

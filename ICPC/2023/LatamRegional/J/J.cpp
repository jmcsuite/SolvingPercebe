#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn=1e5;
pll ans[maxn];
ll block=sqrt(maxn);
ll N;

namespace lca{
    const int maxPow=20;
    ll vl[maxn];
    vll vadj[maxn];
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
        for(int i=0; i<(2*N-1); i++) dp[i][0]=depth[i];
        for(int j=1; j<maxPow; j++) {
            for (int i=0; i<(2*N-1); i++) {
                dp[i][j] = dp[i][j-1];
                int k = i+(1<<(j-1));
                if(k >= 2*N-1) continue;
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

    // call this;
    void preprocess(ll x) {
        t=d=0;
        build(x,x);
        buildPow();
        for (int i=0; i<N; i++) ans[i]={1e9, N-1};
    }
    void calc(ll x) {
        ll b = block*x;
        ll e = min(block*(x+1), N);
        for (ll i = b; i < e; i++) {
            for (ll j = i+1; j < e; j++) {
                ans[i] = min(ans[i], {depth[vl[i]].first + depth[vl[j]].first - 2*depth[vl[query(i,j)]].first, j});
            }
        }
    }

    void prop(ll x) {
        ll b = block*x;
        ll e = min(block*(x+1), N);
        vector<pll> vis(N, {1e9,N-1});
        queue<ll> q;
        for (ll i=b; i<e; i++) {
            q.push(i);
            vis[i]={0,i};
        }

        while (!q.empty()) {
            ll u = q.front(); q.pop();
            for (ll y: vadj[u]) {
                if (vis[y].first < vis[u].first+1) continue;
                if (vis[y].first == vis[u].first+1) {
                    vis[y].second = min(vis[y].second, vis[u].second);
                    continue;
                }
                vis[y] = {vis[u].first+1, vis[u].second};
                q.push(y);
            }
        }
        for (ll i=0; i<b; i++) ans[i] = min(ans[i], vis[i]);
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N;
    for (int i=1; i<N; i++) {
        ll a,b; cin>>a>>b;
        --a; --b;
        lca::vadj[a].push_back(b);
        lca::vadj[b].push_back(a);
    }
    lca::preprocess(0);
    for (ll i = N-1; i>=0; i-=block) {
        lca::calc(i/block);
        lca::prop(i/block);
    }
    for (int i=0; i<N; i++) cout << ++(ans[i].second) << (i+1 == N ? '\n' : ' ');
}

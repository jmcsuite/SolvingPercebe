namespace lca{
    const int maxPow=20; // 2**20 > 10**6
    const int maxn=1e5;
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
        for(int i=0; i<t; i++) dp[i][0]=depth[i];
        for(int j=1; j<maxPow; j++) {
            for (int i=0; i<t; i++) {
                dp[i][j] = dp[i][j-1];
                int k = i+(1<<(j-1));
                if(k >= t) continue;
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
    }
}

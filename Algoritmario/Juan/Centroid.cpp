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
    }
}

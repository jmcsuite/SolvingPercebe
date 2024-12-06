#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 1<<17;
struct segmentTree {
    struct str {
        ll x;
        ll l;
        ll r;
        str() : x(0), l(0), r(0) {}
        str(ll a, ll b, ll c) : x(a), l(b), r(c) {}
    };

    str func(str a, str b) {
        return {max(a.x,b.x), min(a.l, b.l), max(a.r, b.r)};
    }

    str st[2*maxn];
    ll n;

    void build(vll& vl){
        n = vl.size();
        for(int i = 0; i < n;i++) st[i+n] = {vl[i],i,i+1};
        for (int i = n-1; i>0; i--) st[i] = func(st[i*2], st[i*2+1]);
    }

    // 0 index
    void update(int pos, ll x) {
        for(pos+=n, st[pos].x=x, pos/=2; pos; pos/=2) st[pos] = func(st[pos*2], st[pos*2+1]);
    }

    ll searchMaxL(ll i, ll k, ll r) {
        if (st[i].l >= r) return -1;
        if (st[i].x <= k) return -1;
        if (st[i].l+1 == st[i].r) return st[i].l;

        ll t = searchMaxL(i*2+1, k, r);
        if (t != -1) return t;
        return searchMaxL(i*2,k,r);
    }

    ll searchMinL(ll i, ll k, ll l) {
        if (st[i].r <= l) return -1;
        if (st[i].x <= k) return -1;
        if (st[i].l+1 == st[i].r) return st[i].l;

        ll t = searchMinL(i*2, k, l); 
        if (t != -1) return t;
        return searchMinL(i*2+1,k,l);
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin >> N >> M;
    vll vv(N+2); 
    vv[0] = vv[N+1] = 3e9;

    for (int i = 1; i <= N; i++) cin >> vv[i];
    vll vl(maxn);
    for (int i = 0; i < N+1; i++) vl[i] = abs(vv[i]-vv[i+1]);
    segmentTree st;
    st.build(vl);

    while(M--) {
        ll a,b,c;
        cin >> a >> b >> c;
        if (a == 1) {
            vv[b] = c;
            st.update(b-1, abs(vv[b-1]-vv[b]));
            st.update(b, abs(vv[b]-vv[b+1]));
            continue;
        }
        ll maxl = st.searchMaxL(1, c, b);
        ll minl = st.searchMinL(1, c, b);
        cout <<  minl-maxl << '\n';
    }
}

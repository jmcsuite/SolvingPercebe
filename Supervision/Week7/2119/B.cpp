#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;


using ll = long long;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
using vll = vector<ll>;
using set_t = tree<pair<int,int>,null_type, less<pair<int,int>>, rb_tree_tag, tree_order_statistics_node_update>;
const int maxn = 3e5;


vpll vadj[maxn];
namespace lca{
    const int maxPow=20;
    ll vl[maxn];
    pll depth[2*maxn];
    pll dp[2*maxn][maxPow];
    ll t,d;
    ll sum[maxn];
    
    void build(int x, int p) {
        vl[x]=t;
        depth[t++]={d,x};
        for(pll y: vadj[x]) {
            if (y.first == p) continue;
            ++d;
            sum[y.first] = sum[x] + y.second;
            build(y.first,x);
            depth[t++]={d,x};
        }
        --d;
    }

    void buildPow() {
        for (int i=0; i<t; i++) dp[i][0]=depth[i];
        for (int j=1; j<maxPow; j++) {
            for (int i=0; i<t; i++) {
                dp[i][j] = dp[i][j-1];
                int k = i+(1<<(j-1));
                if (k >= t) continue;
                dp[i][j]=min(dp[i][j], dp[k][j-1]);
            }
        }
    }

    ll query(ll _a, ll _b) {
        ll a = min(vl[_a], vl[_b]);
        ll b= max(vl[_a], vl[_b]);
        ll dis = b-a+1;
        ll lz = 63-__builtin_clzll(dis);
        ll k = b-(1<<lz)+1;
        return min(dp[a][lz], dp[k][lz]).second;
    }

    ll dis(ll a, ll b) {
        ll p = query(a, b);
        return sum[a] + sum[b] - 2*sum[p];
    }

    ll disupdate(ll a, ll b) {
        ll p = query(a,b);
        return dis(p, b);
    }

    //call this;
    void preprocess(ll x) {
        t=d=0;
        build(x,x);
        buildPow();
    }
}

ll ans = 0;
set_t st;
void add(ll x) {
    ll t = lca::vl[x];
    ll order = st.order_of_key({t,x});

    if (st.empty()) {
        st.insert({t,x});
        return;
    }

    ll a = (order-1) + st.size(); 
    a %= st.size();
    ll b = (order) % st.size();

    ll u = st.find_by_order(a)->second;
    ll v = st.find_by_order(b)->second;

    ans -= lca::disupdate(u,v);
    ans += lca::disupdate(u,x);
    ans += lca::disupdate(x,v);
    st.insert({t,x});
}

void erase(ll x) {
    ll t = lca::vl[x];
    st.erase(st.find({t,x}));
    ll order = st.order_of_key({t,x});

    if (st.empty()) return;

    ll a = (order-1) + st.size(); 
    a %= st.size();
    ll b = (order) % st.size();

    ll u = st.find_by_order(a)->second;
    ll v = st.find_by_order(b)->second;

    ans += lca::disupdate(u,v);
    ans -= lca::disupdate(u,x);
    ans -= lca::disupdate(x,v);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n; cin>>n;
    for (int i=1; i<n; i++) {
        ll a,b,c; cin>>a>>b>>c;
        --a; --b;
        vadj[a].push_back({b,c});
        vadj[b].push_back({a,c});
    }

    lca::preprocess(0);
    ll q; cin>>q;
    while (q--) {
        char c; ll x;
        cin>>c>>x;
        --x;
        if (c == '+') add(x);
        else erase(x);
        cout << ans << '\n';
    }
}

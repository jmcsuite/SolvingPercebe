#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int mod = 998244353;
const int maxn = (1<<19);
ll fact[2*maxn];
ll inv[2*maxn];
ll cat[maxn];

ll bin_exp(ll a, ll x) {
    ll ans = 1;
    while (x) {
        if (x%2) ans = (ans * a)%mod;
        x/=2;
        a = (a*a)%mod;
    }
    return ans;
}
void pre() {
    fact[0] = 1;
    for (ll i=1; i<2*maxn; i++) {
        fact[i] = (fact[i-1] * i) % mod;
    }
    inv[2*maxn - 1] = bin_exp(fact[2*maxn-1], mod-2);
    for (ll i = 2*maxn-2; i>=0; i--) inv[i] = ((i+1) * inv[i+1])%mod;
    for (ll i=0; i<maxn; i++) cat[i] = (((fact[2*i] * inv[i]) % mod) * inv[i+1])%mod;
}

struct segmentTree {
    struct str {
        ll m,sum;
        str() : m(0), sum(0) {}
        str(ll a, ll b) : m(a), sum(b) {}
    };

    str func(str a, str b) {
        return {max(a.m,b.m), a.sum + b.sum};
    }

    str st[4*maxn];
    ll n;

    void build(int sizn) {
        n = sizn;
        for (int i=0; i<2*n; i++) st[i] = {0,0};
    }

    ll descent(ll p, ll x) {
        if (p >= n) return st[p].m;
        if (st[p*2+1].m >= x) return descent(p*2+1, x);
        return descent(p*2, x);
    }

    ll bin_search(ll r, ll x) {
        for (r+=n; r; r/=2) {
            if (r%2 == 0) continue;
            if (st[--r].m >= x) return descent(r, x);
        }
        return n;
    }

    void update(int pos, str x) {
        for (pos+=n, st[pos]=x,pos/=2; pos; pos/=2) {
            st[pos] = func(st[pos*2],st[pos*2+1]);
        }
    }

    ll query(int l, int r) {
        ll ans = 0;
        for (l+=n, r+=n; l<r; l/=2,r/=2) {
            if (l%2) ans += st[l++].sum;
            if (r%2) ans += st[--r].sum;
        }
        return ans;
    }
};

segmentTree st;
bool se = true;
void solve() {
    ll n; cin>>n;
    map<ll, pll> mp; // [derecha], [izquierda,sum]
    ll pp = 1;
    while (pp < 2*n) pp *= 2;
    st.build(pp);

    ll ans = cat[n];
    mp[2*n] = {-1, 2*n};

    if (se) cout << ans;
    vector<pll> in(n);
    for (int i=0; i<n; i++) cin>>in[i].first>>in[i].second;

    for (int i=0; i<n; i++) {
        ll a = in[i].first;
        ll b = in[i].second;
        a--; b--;
        ll up = (min(st.bin_search(a, b), 2*n));
        ll prevsum = mp[up].second;
        ll sum = b - a - 1 - st.query(a,b);
        ans = (ans * cat[sum/2]) % mod;
        ans = (ans * bin_exp(cat[prevsum/2],mod-2)) % mod;


        mp[up].second -= sum + 2;
        ll nsum = mp[up].second;
        // Debug
        /*
        if (nsum/2 < 0) {
            cout << n << endl;
            for (pll p: in) cout << p.first << ' ' << p.second << endl;
        }
        */
        // Debug

        ans = (ans * cat[nsum/2])%mod;
        if (up != 2*n) st.update(mp[up].first, {up, mp[up].second+2});
        st.update(a, {b,sum+2});
        mp[b] = {a,sum};

        // Debug
        if (se) cout << ' ' << ans;
    }
    if (se) cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    pre();
    ll t; cin>>t;
    while(t--) solve();
}

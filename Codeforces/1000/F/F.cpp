#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int mod = 998244353;
const int maxn = 3e5 + 3;
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
ll p[maxn+1];
ll vl[maxn+1];
ll sum[maxn+1];
ll pans[maxn+1];

ll f(ll x) {
    return (vl[x] == x ? x : vl[x] = f(vl[x]));
}

// a es son, b = p[a];
void join(ll a, ll b) {
    ll pb = f(b);
    pans[a] = pb;
    sum[pb] += sum[a] + 2;
    vl[a] = pb;
}

void clear(ll n) {
    for (int i=0; i<=n; i++) p[i] = vl[i] = i;
    for (int i=0; i<=n; i++) pans[i] = sum[i] = 0;
}

void solve() {
    ll n; cin>>n;
    clear(n);
    ll ans = cat[n];
    cout << ans;

    vector<pll> in(n+1);
    in[0].first = 0; 
    in[0].second = n;
    for (int i=1; i<=n; i++) cin>>in[i].first>>in[i].second;
    vector<pll> bracket;
    for (int i=1; i<=n; i++) {
        bracket.push_back({in[i].first, i});
        bracket.push_back({in[i].second, -1*i});
    }
    sort(bracket.begin(), bracket.end());

    stack<ll> st;
    st.push(0);
    for (pll x: bracket) {
        if (x.second < 0){
            st.pop();
            continue;
        }
        p[x.second] = st.top();
        st.push(x.second);
    }

    for (int i=n; i>0; i--) join(i, p[i]);

    map<ll,ll> mp;
    mp[0] = n*2;
    for (int i=1; i<=n; i++) {
        ll catrange = sum[i];
        ll pa = pans[i];
        ans = (ans * cat[catrange/2])%mod;
        ans = (ans * bin_exp(cat[mp[pa]/2], mod-2))%mod;
        mp[pa] -= catrange + 2;
        ans = (ans * cat[mp[pa]/2])%mod;
        mp[i] = catrange;
        cout << ' ' << ans;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    pre();
    ll t; cin>>t;
    while(t--) solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e5 + 2;
const int mod = 1e9 + 7;

ll bin_exp(ll a, ll x) {
    ll ans = 1;
    while (x) {
        if (x%2) ans = (ans*a)%mod;
        x /= 2;
        a = (a*a)%mod;
    }
    return ans;
}

ll inv[maxn];
ll pp[maxn];

struct segmentTree {
    using str = long long;
    str func(str a, str b) {
        return (a+b)%mod;
    }
    str st[2*maxn];
    ll n;

    void build(int sizn) {
        n = sizn;
        for(int i = 0; i<2*n; i++) st[i] = 0;
    }

    // 0-indexed
    void update(int pos, str x) {
        for (pos+=n, st[pos]=(st[pos]+x)%mod,pos/=2; pos; pos/=2) {
            st[pos] = func(st[pos*2], st[pos*2+1]);
        }
    }

    // [L, R) 0-indexed
    str query(int l, int r) {
        str ansl=0;
        str ansr=0;
        for(l+=n, r+=n; l<r; l/=2,r/=2) {
            if (l%2) ansl=func(ansl, st[l++]);
            if (r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl, ansr);
    }
};

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, Q; string p_in;
    cin >> N >> Q >> p_in;
    while (p_in.size() < 8) p_in.push_back('0');
    ll p_int = 0;
    for (size_t i = 2; i < p_in.size(); i++) {
        p_int *= 10;
        p_int += p_in[i] - '0';
    }
    p_int = 1000000 - p_int; 
    ll p = (p_int * bin_exp(1000000, mod-2))%mod;
    ll pinv = bin_exp(p, mod-2);
    inv[0] = pp[0] = 1;
    for (int i = 1; i < maxn; i++) pp[i] = (pp[i-1]*p)%mod;
    for (int i = 1; i < maxn; i++) inv[i] = (inv[i-1]*pinv)%mod;

    segmentTree l,r; 
    l.build(N);
    r.build(N);

    while (Q--) {
        char c; cin >> c;
        if (c != '?') {
            ll b, x; cin >> b >> x; x--;
            if (c == '-') b*=-1;
            ll lb = (b * inv[x])%mod;
            ll rb = (b * inv[N-1-x])%mod;
            lb = (lb+mod)%mod;
            rb = (rb+mod)%mod;
            l.update(x,lb);
            r.update(x,rb);
            continue;
        }
        ll x; cin >> x; 
        x--;
        ll vl = (l.query(0, x) * pp[x])%mod;
        ll vr = (r.query(x, N) * pp[N-1-x])%mod;
        ll ans = ((vl + vr)%mod + mod)%mod;
        cout << ans << '\n';
    }
}

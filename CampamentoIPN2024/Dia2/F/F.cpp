#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
using vll = vector<ll>;

const int maxn = 1e5 + 2;
const int block = sqrt(maxn);

ll vl[maxn];
ll xx[maxn];
ll bip[maxn];
ll rnk[maxn];
ll n,m,q,sum;

void setup() {
    for (int i=0; i<n; i++) xx[i] = rnk[i] = bip[i] = 0;
    for (int i=0; i<n; i++) vl[i] = i;
    sum = 0;
}
struct op {
    ll a,b,bipb,rankb;
};

ll ff(ll x) {
    return (vl[x] == x ? x : ff(vl[x]));
}
ll xorCalc(ll x) {
    return (vl[x] == x ? xx[x] : xx[x] ^ xorCalc(vl[x]));
}
op un(ll a, ll b) {
    ll pa = ff(a);
    ll pb = ff(b);
    if (pa == pb) {
        ll ba = bip[pa];
        ll ra = rnk[pa];

        ll disa = xorCalc(a);
        ll disb = xorCalc(b);
        if (ba == 1) return {pa, pb, ba, ra};
        ll nb = (disa == disb ? 1 : 0);
        if (nb > ba) sum++;
        bip[pa] = nb;
        return {pa, pb, ba, ra};
    }

    if (rnk[pa] > rnk[pb]) {
        swap(pa, pb);
        swap(a,b);
    }

    ll bb = bip[pb];
    ll rb = rnk[pb];

    ll disa = xorCalc(a);
    ll disb = xorCalc(b);
    ll disp = disa ^ disb ^ 1ll;

    xx[pa] = disp;
    vl[pa] = pb;
    if (rnk[pa] == rnk[pb]) rnk[pb]++;
    if (bip[pa]) bip[pb] = 1;
    if (bip[pb] > bb) sum++;
    return {pa, pb, bb, rb};
}

void rev(op o) {
    vl[o.a] = o.a;
    xx[o.a] = 0;
    rnk[o.b] = o.rankb;

    if (bip[o.b] > o.bipb) sum--;
    bip[o.b] = o.bipb;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>q;
    vector<pll> ep(m);
    for (int i=0; i<m; i++) {
        cin>>ep[i].first>>ep[i].second;
        ep[i].first--; ep[i].second--;
    }

    vector<pair<pll,ll>> vq(q);
    for (int i=0; i<q; i++) {
        cin>>vq[i].first.first>>vq[i].first.second;
        vq[i].first.first--;
        vq[i].second = i;
    }

    sort(vq.begin(), vq.end(), [&](pair<pll,ll> a, pair<pll,ll> b) {
            ll ba = a.first.first/block;
            ll bb = b.first.first/block;
            if (ba != bb) return ba < bb;
            return a.first.second < b.first.second;
            });

    vector<ll> ans(q);
    ll prev = -1;
    ll i = -1;
    for (pair<pll,ll> p: vq) {
        ll b = p.first.first / block;
        if (b != prev) {
            setup();
            sum = 0;
            prev = b;
            i = (b+1)*block;
        }
        while (i < p.first.second) {
            un(ep[i].first, ep[i].second);
            i++;
        }
        stack<op> st;
        for (int j=p.first.first; j < p.first.second && j < (b+1)*block; j++) {
            st.emplace(un(ep[j].first, ep[j].second));
        }
        ans[p.second] = sum;
        while (!st.empty()) {
            rev(st.top());
            st.pop();
        }
    }

    for (int i=0; i<q; i++) cout << (ans[i] == 0 ? "Possible\n" : "Impossible\n");
}

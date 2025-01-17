#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxA = 1e4; 
const int maxn = 1e3 + 1;
const int maxc = 2500 + 1;

ll temp[maxc];

struct segmentTree{
    struct str{
        ll t; 
        ll c;
        str() : t(0), c(1) {}
        str(ll _t, ll _c) : t(_t), c(_c) {}
    };

    str st[2*maxA];
    ll n; ll h; ll d[2*maxn];

    str merge(str a, str b) {
        if (a.t < b.t) return b;
        return a;
    }


    void build(ll sz) {
        n=sz;
        h=64-__builtin_clzll(n);
        for (int i=0; i<n; i++) st[i+n] = {};
        for (int i=n-1; i>0; i--) st[i]= {};
    }

    void compute() {
        for (int i=1; i<n; i++) {
            st[i*2] = merge(st[i], st[i*2]);
            st[i*2+1] = merge(st[i], st[i*2+1]);
        }

        for (int i=0; i<n; i++) temp[st[i+n].c]++;
    }

    void update(ll l, ll r, str x) {
        for (l+=n,r+=n; l<r; l/=2,r/=2) {
            if(l%2) st[l++] = x;
            if(r%2) st[--r] = x;
        }
    }
};

ll ans[maxc];
struct rect{
    ll x1,y1,x2,y2,c;
};

rect vl[maxn];

struct query{
    ll x;
    ll add;
    ll i;
    query(ll _x, ll a, ll b) : x(_x), add(a), i(b) {}
    bool operator < (const query& other) const {
        return x < other.x;
    }
};

ll active[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll A,B,n; cin>>A>>B>>n;
    for (int i=0; i<n; i++) {
        cin >> vl[i].x1 >> vl[i].y1 >> vl[i].x2 >> vl[i].y2 >> vl[i].c;
    }

    vector<query> vq;
    for (int i=0; i<n; i++) {
        vq.push_back({vl[i].x1, 1, i});
        vq.push_back({vl[i].x2, -1, i});
    }
    sort(vq.begin(), vq.end());
    
    segmentTree st; 
    size_t i,k;
    i = k = 0;
    ll prev = 0;
    temp[1] = B;
    while (i < vq.size()) {
        while (k < vq.size() && vq[k].x == vq[i].x) k++;
        for (size_t z=i; z<k; z++) active[vq[z].i] += vq[z].add;
        for (int c=0; c<maxc; c++) ans[c] += temp[c] * (vq[i].x - prev);
        for (int c=0; c<maxc; c++) temp[c] = 0;


        prev = vq[i].x;
        st.build(B);

        for (int i=0; i<n; i++) {
            if (active[i] == 0) continue;
            st.update(min(vl[i].y1, vl[i].y2), max(vl[i].y1, vl[i].y2), {i+1, vl[i].c});
        }
        st.compute();
        i = k;
    }

    for (int c=0; c<maxc; c++) ans[c] += temp[c] * (A - prev);

    for (int c=0; c<maxc; c++) {
        if (ans[c] == 0) continue;
        cout << c << ' ' << ans[c] << '\n';
    }
}

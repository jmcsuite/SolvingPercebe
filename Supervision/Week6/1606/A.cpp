#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 50005;
const int maxx = 100005;
const int minx = 0;

ll fi[maxx];
ll last[maxx];

ll lef[maxn];
ll righ[maxn];
ll nleft[maxn];
ll nright[maxn];


ll cl[maxn];
ll cr[maxn];
ll nl[maxn];
ll nr[maxn];

ll n;

ll dpl(ll x);
ll dpr(ll x);

ll dpl(ll x) {
    if (x == n) return 0;
    if (cl[x] != 0) return cl[x];
    ll a1 = dpl(lef[x]);
    ll a2 = 1 + dpr(nright[x]);
    nl[x] = ( (a1 > a2) ? lef[x] : nright[x]);
    return cl[x] = max(a1, a2);
}

ll dpr(ll x) {
    if (x == n) return 0;
    if (cr[x] != 0) return cr[x];
    ll a1 = dpr(righ[x]);
    ll a2 = 1 + dpl(nleft[x]);
    nr[x] = ( (a1 > a2) ? righ[x] : nleft[x]);
    return cr[x] = max(a1, a2);
}

struct segmentTree {
    struct str {
        ll first;
        ll second;
        str() : first(0), second(0) {}
        str(ll a, ll b) : first(a), second(b) {}
    };

    str func(str a, str b) {
        if (a.first < b.first) return b;
        return a;
    }

    str st[2*maxn];
    ll n;

    void build(vpll& vl, int sizn) {
        n = sizn;
        for(int i=0; i<n; i++) st[i+n] = {vl[i].first,vl[i].second};
        for(int i=n-1; i>0; i--) st[i] = func(st[i*2],st[i*2+1]);
    }

    // 0-indexed;
    void update(int pos, str x) {
        for (pos+=n, st[pos]=x, pos/=2; pos; pos/=2) {
            st[pos] = func(st[pos*2],st[pos*2+1]);
        }
    }

    str query(int l, int r) {
        str ansl={0,n};
        str ansr={0,n};
        for (l+=n,r+=n; l<r; l/=2,r/=2) {
            if (l%2) ansl=func(ansl,st[l++]);
            if (r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl, ansr);
    }
};

pair<pll,ll> vl[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for (int i=0; i<n; i++) {
        cin>>vl[i].first.first>>vl[i].first.second;
        vl[i].second = i;
    }
    sort(vl, vl+n);
    for (int i=0; i<n; i++) last[vl[i].first.first] = i;
    for (int i=n-1; i>=0; i--) fi[vl[i].first.first] = i;

    vpll vp(n);
    for (int i=0; i<n; i++) {
        vp[i].first = vl[i].first.second;
        vp[i].second = vl[i].second;
    }
    segmentTree st; 
    st.build(vp, n);

    sort(vl, vl+n, [&](pair<pll,ll>& a, pair<pll,ll>& b) {
                if (a.first.second > b.first.second) return true;
                return false;
            });

    ll j = 0;
    for (int i=0; i<n; i++) {
        if (i != j) continue;
        while (j < n && vl[i].first.second == vl[j].first.second) j++;
        for (int k = i; k < j; k++) {
            lef[vl[k].second] = st.query(0, fi[vl[k].first.first]).second;
            righ[vl[k].second] = st.query(last[vl[k].first.first]+1, n).second;
        }

        ll b = fi[vl[i].first.first];
        ll e = last[vl[i].first.first];
        for (int k = b; k<=e; k++) st.update(k, {0,n});

        for (int k = i; k < j; k++) {
            nleft[vl[k].second] = st.query(0, fi[vl[k].first.first]).second;
            nright[vl[k].second] = st.query(last[vl[k].first.first]+1, n).second;
        }
    }

    bool l = true;
    pll ans;
    ans.first = 0;
    // xd
    for (int i=n-1; i>=0; i--) {
        ll p = dpl(vl[i].second);
        if (p > ans.first) {
            l = true;
            ans.first = p;
            ans.second = vl[i].second;;
        }

        ll q = dpr(vl[i].second);
        if (q > ans.first) {
            l= false;
            ans.first = q;
            ans.second = vl[i].second;
        }
    }

    sort(vl, vl+n, [&](pair<pll,ll>& a, pair<pll,ll>& b) {
            return a.second < b.second;
            });

    ll a = ans.second;
    ll b = (l ? nl[a] : nr[a]);
    vll pp;
    while (b != n) {
        if (l && (vl[b].first.first > vl[a].first.first)) {
            pp.push_back(a);
            l = !l;
        }
        else if ((!l) && (vl[a].first.first > vl[b].first.first)) {
            pp.push_back(a);
            l = !l;
        }
        a = b;
        b = (l ? nl[a] : nr[a]);
    }
    pp.push_back(a);
    cout << ans.first << '\n';
    for (size_t i=0; i< pp.size(); i++) cout << pp[i] + 1 << (i+1 == pp.size() ? '\n' : ' ');
}

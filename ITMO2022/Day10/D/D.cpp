#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 150010;
namespace suffix {
ll p[maxn], c[maxn], np[maxn], nc[maxn], cfreq[maxn], lcp[maxn];
ll n;

void pro(ll h) {
    for (int i=0; i<n; i++) {
        np[i] = p[i] - (1<<h);
        if (np[i] < 0) np[i] += n;
    }
    for (int i=0; i<n; i++) cfreq[i]=0;
    for (int i=0; i<n; i++) cfreq[c[i]]++;
    for (int i=1; i<n; i++) cfreq[i] += cfreq[i-1];
    
    for (int i=n-1; i>=0; i--) p[--cfreq[c[np[i]]]] = np[i];
    nc[p[0]] = 0;
    for (int i=1; i<n; i++) {
        ll a = (p[i] + (1<<h));
        ll b = p[i-1] + (1<<h);
        if (a >= n) a -= n;
        if (b >= n) b -= n;
        nc[p[i]] = nc[p[i-1]];
        if (c[p[i]] != c[p[i-1]] || c[a] != c[b]) nc[p[i]]++;
    }
    for (int i=0; i<n; i++) c[i] = nc[i];
}

void pre(vector<int> s) {
    vpll vp(n);
    for (int i=0; i<n; i++) vp[i] = {s[i],i};
    sort(vp.begin(),vp.end());
    for (int i=0; i<n; i++) p[i] = vp[i].second;

    c[vp[0].second] = 0;
    for (int i=1; i<n; i++) {
        c[vp[i].second] = c[vp[i-1].second];
        if (vp[i-1].first != vp[i].first) c[vp[i].second]++;
    }
}

void lcp_build(vector<int> s) {
    ll k = 0;
    for (int i=0; i<n; i++) {
        if (c[i] == n-1) {
            k=0;
            continue;
        }
        ll j=p[c[i]+1];
        for(;i+k < n && j+k < n && s[i+k] == s[j+k]; k++) {}
        lcp[c[i]] = k;
        k--;
        if (k<0) k=0;
    }
}

void build(vector<int> s) {
    n = s.size();
    pre(s);
    for (ll h=0; (1<<h) < n; h++) pro(h);
    lcp_build(s);
}
}

struct segmentTree{
struct str {
    ll pre, suff, ans, sz;
    str() : pre(0),suff(0),ans(0),sz(1) {}
    str(ll x) : pre(x), suff(x), ans(x), sz(1) {}
    str(ll a,ll b, ll c,ll d) : pre(a), suff(b), ans(c), sz(d) {}
};

str func(str a, str b) {
    str c;
    c.sz = a.sz + b.sz;
    c.ans = max(a.ans, b.ans);
    c.ans = max(c.ans, a.suff + b.pre);
    c.pre = (a.pre == a.sz ? a.sz + b.pre : a.pre);
    c.suff = (b.suff == b.sz ? b.sz + a.suff : b.suff);
    return c;
}

str st[2*maxn];
ll n;

void build(int sizn) {
    n = sizn;
    for (int i=0; i<n; i++) st[i+n] = {};
    for (int i=n-1; i>0; i--) st[i] = func(st[i*2], st[i*2+1]);
}

void update(int pos, int x) {
    for(pos+=n,st[pos]={x},pos/=2; pos; pos/=2) {
        st[pos] = func(st[pos*2],st[pos*2+1]);
    }
}

ll query(int l, int r) {
    str ansl(0,0,0,0);
    str ansr(0,0,0,0);
    for (l+=n,r+=n; l<r;l/=2,r/=2) {
        if (l%2) ansl=func(ansl,st[l++]);
        if (r%2) ansr=func(st[--r],ansr);
    }
    return func(ansl,ansr).ans;
}
};
segmentTree st;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll n,m; cin>>n>>m;
    vector<int> vl(n+1);
    for (int i=0; i<n; i++) cin>>vl[i];
    suffix::build(vl);
    st.build(n+2);

    vector<vll> vadj(n+2);

    ll ans = n;
    ll sz = n; // lcp = sz, ans/sz = rep

    for (int i=1; i<=n; i++) vadj[suffix::lcp[i]].push_back(i);
    
    for (int i=n; i>0; i--) {
        // sz = i;
        // rep = st.query(0,n+2);
        for (ll x: vadj[i]) st.update(x,1);
        ll rep = st.query(0,n+2);
        rep++;
        if (i * rep > ans) {
            ans = i*(rep);
            sz = i;
        }
    }
    cout << ans << '\n';
    cout << sz << '\n';

    if (ans == n) {
        for (int i=0; i<n; i++) cout << vl[i] << ' ';
        cout << '\n';
        return 0;
    }
    set<pll> ss;
    ll rep = ans/sz;
    rep--;
    for (int i=1; i<=rep; i++) ss.insert({suffix::lcp[i],i});
    for (int i=1; i<n; i++) {
        if (ss.begin() -> first == sz) {
            for (int k=0,j = suffix::p[i]; k < sz; k++,j++) cout << vl[j] << ' ';
            cout << '\n';
            return 0;
        }
        ss.erase({suffix::lcp[i], i});
        ss.insert({suffix::lcp[i+rep], i+rep});
    }
}

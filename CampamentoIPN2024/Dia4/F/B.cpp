#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll= vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
const long long INF = 1e18 * 3;

struct slope {
    ll m,a;
    ll eval(ll x) {return x*m + a;}
    bool operator< (const slope& other) const {
        if (m != other.m) return m < other.m;
        return a > other.a;
    }
};

namespace cht {
    // gets minimum
    // increasing queries
    // non-increasing (decreasing) slopes

    // does b intersect base before a
    bool remove(slope base, slope a, slope b) {
        ll deltaa = ((base.a - a.a)) * (b.m - base.m);
        ll deltab = ((base.a - b.a)) * (a.m - base.m);
        return deltaa >= deltab;
    }

    void add(list<slope>& dq, slope x) {
        if (dq.empty()) {
            dq.push_back(x);
            return;
        }

        slope a = dq.back(); 
        if (a.m == x.m) return;
        if (dq.size() == 1) {
            dq.push_back(x);
            return;
        }

        dq.pop_back();
        slope base = dq.back();
        while (remove(base, a, x)) {
            a = base;
            dq.pop_back();
            if (dq.empty()) break;
            base = dq.back();
        }
        dq.push_back(a);
        if (x.m != a.m) dq.push_back(x);
    }

    ll getmin(list<slope>& dq, ll x) {
        if (dq.empty()) return INF;
        if (dq.size() == 1) return dq.front().eval(x);
        slope a = dq.front();
        dq.pop_front();
        slope b = dq.front();
        while (b.eval(x) <= a.eval(x)) {
            a = b;
            dq.pop_front();
            if (dq.empty()) break;
            b = dq.front();
        }
        dq.push_front(a);
        return dq.front().eval(x);
    }
};

const int maxn = 3e5;
struct segmentTree {
    list<slope> st[2*maxn];
    ll n;
    void build(ll sz) {
        n = sz;
    }

    void update(ll l, ll r, slope x) {
        for (l+=n,r+=n; l<r; l/=2,r/=2) {
            if (l%2) cht::add(st[l++],x);
            if (r%2) cht::add(st[--r],x);
        }
    }

    ll query(ll l, ll q) {
        ll ans = INF;
        for (l+=n; l; l/=2) {
            ans = min(ans, cht::getmin(st[l],q));
        }
        return ans;
    }
};

vector<pll> q;
vector<pair<slope,pll>> ins;

bool tt[maxn];
pair<slope,pll> vl[maxn];
segmentTree st;

int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    ll Q; cin>>Q;
    for (int i=0; i<Q; i++) {
        ll t; cin>>t;
        if (t == 3) {
            ll x; cin>>x;
            q.push_back({x,i});
            continue;
        }
        if (t == 1) {
            tt[i] = true;
            slope s; cin>>s.m>>s.a;
            vl[i] = {s,{i,Q}};
            continue;
        }
        ll id; cin>>id; --id;
        vl[id].second.second = i;
    }
    for (int i=0; i<Q; i++) {
        if (!tt[i]) continue;
        ins.push_back(vl[i]);
    }
    sort(ins.begin(), ins.end());

    st.build(Q);
    for (auto in : ins) {
        st.update(in.second.first, in.second.second, {in.first.m*-1, in.first.a*-1});
    }

    vector<pll> ans;
    sort(q.begin(), q.end());
    for (auto p: q) {
        ll x = st.query(p.second, p.first) * -1;
        ans.push_back({p.second, x});
    }
    sort(ans.begin(), ans.end());
    for (auto p: ans) {
        if (p.second == -1*INF) cout << "EMPTY SET\n";
        else cout << p.second << '\n';
    }
}


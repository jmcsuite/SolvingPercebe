#include <bits/stdc++.h>
using namespace std;
using ll = int;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = (1<<17); // maybe
ll vl[maxn], xx[maxn], rk[maxn];
pll qq[maxn];
ll comps,sum,nnn;

ll ff(ll x) {
    while (x != vl[x]) x = vl[x];
    return x;
}

ll XX(ll x) {
    ll ans = xx[x];
    while (x != vl[x]) {
        x = vl[x];
        ans ^= xx[x];
    }
    return ans;
}

stack<int> s;

void un(ll a, ll b) {
    ll pa = ff(a); ll pb = ff(b);
    if (rk[pa] > rk[pb]) {
        swap(a,b);
        swap(pa,pb);
    }

    if (pa == pb) {
        if (sum > 0 || (XX(a) != XX(b))) return;
        sum++;
        s.emplace(pa);
        return;
    }

    comps--;
    xx[pa] = XX(a) ^ XX(b) ^ 1;
    vl[pa] = pb;
    rk[pb] += rk[pa];
    s.emplace(pa);
}

void roll() {
    int x = s.top(); int y = vl[x];
    s.pop();
    if (x == y) {
        sum--;
        return;
    }
    comps++;
    vl[x] = x;
    xx[x] = 0;
    rk[y] -= rk[x];
}

struct segmentTree {
    typedef vector<pll> str;
    str st[2*maxn];
    const int n = maxn;

    void add(int l, int r, pll p) {
        for (l+=n,r+=n; l<r; l/=2,r/=2) {
            if (l%2) st[l++].push_back(p);
            if (r%2) st[--r].push_back(p);
        }
    }

    bool res[maxn];
    void calc(ll x) {
        int ssz = s.size();
        for (size_t i=0; i<st[x].size(); i++) un(st[x][i].first,st[x][i].second);
        //for (pll p: st[x]) un(p.first,p.second);
            //if (sum > 0 && comps == 1) continue;

        if (x >= n) {
            ll idx = x-n;
            if (comps > 1) {
                res[idx] = false;
            }
            else if (sum > 0) {
                res[idx] = true;
            }
            else {
                ll dis = (nnn%2) ^ XX(qq[idx].first) ^ XX(qq[idx].second);
                if (dis) res[idx] = true;
            }

            while ((int)s.size() > ssz) roll();
            return;
        } 

        calc(x*2);
        calc(x*2+1);
        while ((int)s.size() > ssz) roll();
    }
};
segmentTree st;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n,m,q; cin>>n>>m>>q;
    for (int i=0; i<n; i++) vl[i] = i;
    for (int i=0; i<n; i++) rk[i] = 1;
    nnn = comps = n;

    map<pll,ll> mp;
    for (int i=0; i<m; i++) {
        ll a,b; cin>>a>>b;
        --a; --b;
        mp[{a,b}]=0;
    }

    vector<ll> mm;
    for (int i=0; i<q; i++) {
        ll tt; ll a, b; cin>>tt>>a>>b;
        a--; b--;

        if (tt == 2) {
            mm.push_back(i);
            qq[i].first = a;
            qq[i].second = b;
            continue;
        }
        pll p; 
        p.first = a; p.second = b;
        auto it = mp.find(p);
        if (it == mp.end()) {
            mp[p] = i;
            continue;
        }
        st.add(it->second,i,p);
        mp.erase(it);
    }
    for (auto p: mp) {
        st.add(p.second, q,p.first);
    }
    st.calc(1);

    for (ll x: mm) {
        cout << (st.res[x] ? "Yes\n" : "No\n");
    }
}

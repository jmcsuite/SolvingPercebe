#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn=8;

struct cube {
    ll a,b,c,d,e,f;
    cube() : a(0), b(0), c(0), d(0), e(0), f(0) {}
    cube(ll _a, ll _b, ll _c, ll _d, ll _e, ll _f) :
        a(_a), b(_b), c(_c), d(_d), e(_e), f(_f) {}
    
    bool operator < (const cube& other) const {
        if (a!=other.a) return a<other.a;
        if (b!=other.b) return b<other.b;
        if (c!=other.c) return c<other.c;
        if (d!=other.d) return d<other.d;
        if (e!=other.e) return e<other.e;
        if (f!=other.e) return f<other.f;
        return false;
    }

    cube colplus() {
        return {a,b,f,c,d,e};
    }

    cube colminus() {
        return {a,b,d,e,f,c};
    }

    cube rowminus() {
        return {c,e,b,d,a,f};
    }

    cube rowplus() {
        return {e,c,a,d,b,f};
    }
};

map<cube,ll> dp[8][8];

using node = pair<pll,cube>;
map<cube,node> pr[8][8];
void dijkstra(ll ii, ll jj, cube c) {
    set<pair<ll,node>> st;
    dp[ii][jj][c] = c.e;
    pr[ii][jj][c] = {{ii,jj}, c};
    st.insert({c.e, {{ii,jj}, c}});

    // stop using c, i, j;
    while (!st.empty()) {
        pair<ll,node> item = *st.begin();
        st.erase(st.begin());
        pll p = item.second.first;
        ll d = item.first;
        c = item.second.second;

        if (dp[p.first][p.second][c] < d) continue;
        node thisnode = {p, c};

        node nextnode;
        cube c_next = c.colplus();
        nextnode.first.first = p.first; 
        nextnode.first.second = p.second+1;
        nextnode.second = c_next;
        if (p.second < 7) { /////
            map<cube,ll> &mp = dp[p.first][p.second+1];
            if (mp.find(c_next) == mp.end() || mp[c_next] > d + c_next.e) {
                mp[c_next] = d + c_next.e;
                pr[p.first][p.second+1][c_next] = thisnode;
                st.insert({d+c_next.e,nextnode});
            }
        }

        c_next = c.colminus();
        nextnode.first.first = p.first; 
        nextnode.first.second = p.second-1;
        nextnode.second = c_next;
        if (p.second > 0) { /////
            auto &mp = dp[p.first][p.second-1];
            if (mp.find(c_next) == mp.end() || mp[c_next] > d + c_next.e) {
                mp[c_next] = d + c_next.e;
                pr[p.first][p.second-1][c_next] = thisnode;
                st.insert({d+c_next.e,nextnode});
            }
        }

        c_next = c.rowplus();
        nextnode.first.first = p.first+1;
        nextnode.first.second = p.second;
        nextnode.second = c_next;
        if (p.first < 7) { /////
            auto &mp = dp[p.first+1][p.second];
            if (mp.find(c_next) == mp.end() || mp[c_next] > d + c_next.e) {
                mp[c_next] = d + c_next.e;
                pr[p.first+1][p.second][c_next] = thisnode;
                st.insert({d+c_next.e,nextnode});
            }
        }

        c_next = c.rowminus();
        nextnode.first.first = p.first-1;
        nextnode.first.second = p.second;
        nextnode.second = c_next;
        if (p.first > 0) { /////
            auto &mp = dp[p.first-1][p.second];
            if (mp.find(c_next) == mp.end() || mp[c_next] > d + c_next.e) {
                mp[c_next] = d + c_next.e;
                pr[p.first-1][p.second][c_next] = thisnode;
                st.insert({d+c_next.e,nextnode});
            }
        }
    }
}

vector<string> tr(vector<pll>& vl) {
    vector<string> ans;
    for (pll p: vl) {
        char r = p.first + '1';
        char c = p.second + 'a';
        string s; s.push_back(c); s.push_back(r);
        ans.push_back(s);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    pll x,y; ll a,b,c,d,e,f;
    char cb; 
    char ce;
    cin >> cb >> x.first >> ce >> y.first; 
    cin >> a >> b >> c >> d >> e >> f;
    x.first--; y.first--;
    x.second = cb - 'a';
    y.second = ce - 'a';
    cube cc(a,b,c,d,e,f);
    dijkstra(x.first, x.second, cc);

    ll ans = 1e15;
    vector<pll> sol; 
    pll pp; 
    cube prevc;
    for (auto p: dp[y.first][y.second]) {
        if (p.second < ans) {
            ans = min(p.second, ans);
            prevc = p.first;
        }
    }

    pp.first = y.first; pp.second = y.second;
    while (pp.first != x.first || pp.second != x.second || prevc < cc || cc < prevc) {
        sol.push_back(pp);
        node myn = pr[pp.first][pp.second][prevc];
        prevc = myn.second;
        pp = myn.first;
    }

    sol.push_back(pp);
    reverse(sol.begin(), sol.end());

    vector<string> to_print = tr(sol);
    cout << ans;
    for (string s: to_print) cout << ' ' << s;
    cout << '\n';
}

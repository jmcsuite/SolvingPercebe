#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

struct CHT {
    struct Frac{
        //__int128 x; 
        //__int128 y;
        ll x,y;
        bool operator<(const Frac& other) const {
            return (other.y * x) < (other.x * y);
        }

        bool operator==(Frac other) const {
            return (other.y * x) == (other.x*y);
        }

        Frac(ll a, ll b) : x(a), y(b) {}
        Frac(ll a) : x(a), y(1) {}
    };

    map<ll,ll> mp;
    map<Frac, ll> qrange;
    Frac INF={(1ll<<32),1};

    Frac Intersect(map<ll,ll>::iterator a, map<ll,ll>::iterator b) {
        return {a->second - b->second, b->first - a->first};
    }

    ll prevInf = -1;

    bool Check(ll m, ll x) {
        if (mp.find(m) != mp.end()) {
            if (mp[m] >= x) return false;

            // remove intersect;
            auto it = mp.find(m); 
            auto n = ++it; --it;
            if (n == mp.end()) {
                qrange.erase(INF);
                prevInf = it->first * -1;
            }
            else {
                if (Intersect(it,n) == INF) {
                    cout << "FF" << endl;
                }
                qrange.erase(Intersect(it, n));
            }

            if (it == mp.begin()) return true;
            auto xx = --it; ++it;
            qrange.erase(Intersect(xx, it));
            // add this algoritmario

            return true;
        }
        auto y = mp.upper_bound(m);
        if (y==mp.begin()) return true;

        if (y==mp.end()) {
            //qrange[INF]=m;
            qrange.erase(INF);
            prevInf = m*-100;
            return true;
        }
        auto u = (--y); ++y;

        Frac sec = Intersect(u,y);
        Frac cross = {u->second - x , m - u->first};
        if (sec<cross) return false;
        if (sec == INF) {
            cout << "FF" << endl;
        }
        qrange.erase(sec);
        return true;
    }

    void UpdateQRange(map<ll,ll>::iterator it) {
        auto x = ++it; --it;
        if (x == mp.end()) qrange[INF] = it->first;
        else qrange[Intersect(it,x)] = it->first;
        if (it->first == 29) {
            cout << qrange[INF] << endl;
            cout << (x == mp.end() ? "YES" : "NO") << endl;
        }
    }

    void UpdateRight(ll m) {
        auto it = mp.find(m);
        auto x = ++it; --it;
        if (x == mp.end()) return;
        while(1) {
            auto y = ++x; --x;
            if (y == mp.end()) return;
            Frac sec = Intersect(y,x);
            Frac cross = Intersect(y, it);
            if (cross<sec) return;
            
            if (sec == INF) {
                cout << "FF" << endl;
            }
            cout << (qrange.find(INF) == qrange.end() ? "MLOKOM" : "MGGGM") << endl;
            cout << sec.x << ' ' << sec.y;
            cout << (qrange.find(sec) == qrange.end()) << endl;
            qrange.erase(sec);
            if (m == 12 && prevInf == -2900) {
                cout << (qrange.find(INF) == qrange.end() ? "MLOKO" : "MGGG") << endl;
                cout << (ll)sec.x << ' ' << (ll)sec.y << endl;
                cout << (ll)INF.x << ' ' << (ll)INF.y << endl;
            }
            mp.erase(x);
            x=y;
        }
    }

    void UpdateLeft(ll m) {
        auto it = mp.find(m);
        if (it==mp.begin()) return;
        auto x = --it; ++it;

        while (x != mp.begin()) {
            auto y=--x;++x;
            Frac sec = Intersect(y,x);
            Frac cross = Intersect(y,it);
            if (sec < cross) return;
            if (sec == INF) {
                cout << "FF" << endl;
            }
            qrange.erase(sec);
            mp.erase(x);
            x=y;
        }
    }

    void Add(ll m, ll x) {
        if (!Check(m,x)) return;
        if (m == 12 && prevInf == -2900) {
            cout << (qrange.find(INF) == qrange.end() ? "LOK" : "GG") << endl;
        }

        mp[m]=x;
        UpdateRight(m);
        if (m == 12 && prevInf == -2900) {
            cout << (qrange.find(INF) == qrange.end() ? "LOKO" : "GGG") << endl;
        }
        UpdateLeft(m);
        if (m == 12 && prevInf == -2900) {
            cout << (qrange.find(INF) == qrange.end() ? "LOKOL" : "GGGG") << endl;
        }
        auto it = mp.find(m);
        UpdateQRange(it);
        if (prevInf == -2900) {
            cout << (qrange.find(INF) == qrange.end() ? "FOK" : "Good") << endl;
        }
        if (it == mp.begin()) return;
        --it;
        UpdateQRange(it);
    }

    ll Eval(map<ll,ll>::iterator it, ll x) {
        if (it == mp.end()) {
            cout << prevInf << ' ' << x << endl;
            for (auto p: mp) cout << p.first << ' ' << p.second << endl;
            cout << endl;
            for (auto p: qrange) cout << (ll)p.first.x << ' ' << (ll)p.first.y << ' ' << p.second << endl;
            cout << endl;
            while (1) {
                --it;
                ++it;
            }
        }
        return it->first * x + it->second;
    }

    ll GetMax(ll x) {
        auto it = qrange.lower_bound(x);
        return Eval(mp.find(it->second),x);
    }
};

const int maxn = 150001;
ll depth[maxn];
ll BottomUp[maxn];
ll TopDown[maxn];
ll Sum[maxn];
long long vl[maxn];
ll pa[maxn];
vll vadj[maxn];

struct ST {
    CHT Bot;
    CHT Top;
    vll vadj;
};

ll ans = 0;
ST st[maxn];

void Merge(ll x, ll v) {
    if (st[x].vadj.size() > st[v].vadj.size()) swap(st[x], st[v]);
    ll p = pa[v];
    
    for (ll a : st[x].vadj) {
        ll tp = BottomUp[a]-BottomUp[v]+Sum[v]*(depth[v]-depth[a]);
        tp = tp - Sum[p]*(depth[a]-2*depth[v]+1) - TopDown[p];
        tp = tp + st[v].Top.GetMax(depth[a]-2*depth[v]+1);
        ans = max(ans, tp);
    }

    for (ll a : st[x].vadj) {
        ll tp = TopDown[a] - TopDown[p] - BottomUp[v];
        tp = tp + Sum[a]*(1-2*depth[v])+Sum[p]*(2*depth[v]-1)+Sum[v]*depth[v];
        tp = tp + st[v].Bot.GetMax(Sum[a]-Sum[p]-Sum[v]);
        ans = max(ans, tp);
    }

    for (ll b : st[x].vadj) {
        st[v].Top.Add(Sum[b], TopDown[b]);
        st[v].Bot.Add(depth[b], BottomUp[b]);
        st[v].vadj.push_back(b);
    }
}

void DFS(ll x, ll p) {
    depth[x] = depth[p]+1;
    Sum[x] = Sum[p]+vl[x];
    BottomUp[x] = BottomUp[p] + Sum[x];
    TopDown[x] = TopDown[p] + vl[x] * depth[x]; 
    pa[x] = p;

    ans = max(ans, BottomUp[x]);
    ans = max(ans, TopDown[x]);

    for (ll y: vadj[x]) {
        if (y == p) continue;
        DFS(y,x);
        Merge(y, x);
    }
    if (st[x].vadj.size() > 0) return;
    st[x].vadj.push_back(x);
    st[x].Top.Add(Sum[x],TopDown[x]);
    st[x].Bot.Add(depth[x], BottomUp[x]);
}
struct Frac{
    //__int128 x; 
    //__int128 y;
    ll x,y;
    bool operator<(const Frac& other) const {
        return (other.y * x) < (other.x * y);
    }

    bool operator==(Frac other) const {
        return (other.y * x) == (other.x*y);
    }

    Frac(ll a, ll b) : x(a), y(b) {}
    Frac(ll a) : x(a), y(1) {}
};

map<Frac, ll> m;
Frac INF={(1ll<<31),1};
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    m[INF] = 29;
    Frac sec(88,-13);
    Frac s(14,-2);
    m.erase(s);
    m.erase(sec);
    for (auto p : m) cout << p.first.x << ' ' << p.first.y << endl;
}

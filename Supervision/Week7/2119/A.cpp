#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=3e5;

vpll vadj[maxn];
ll sum[maxn];

namespace LCA{
    const int maxPow = 22; 
    int lifting[maxn][maxPow];
    int in[maxn];
    int sz[maxn];
    int timeTransversal=0;

    void clear() {
        timeTransversal=0;
    }

    void build(int x, int p) {
        lifting[x][0] = p;
        in[x]=timeTransversal++;
        for (int i=0; i<maxPow-1; i++) lifting[x][i+1] = lifting[lifting[x][i]][i]; 
        for (pll y: vadj[x]) {
            if (y.first == p) continue;
            sum[y.first] = sum[x] + y.second;
            build(y.first, x);
        }
        sz[x]=timeTransversal-in[x];
    }

    bool isAncestor(int x, int y) { // x ancestor of y;
        return (in[x] <= in[y] && in[x]+sz[x] > in[y]);
    }

    int lca(int x, int y) {
        if(isAncestor(x,y)) return x;
        if(isAncestor(y,x)) return y;
        // Moving x;
        for(int pow2 = maxPow-1; pow2>=0; pow2--) {
            if (!isAncestor(lifting[x][pow2], y)) x = lifting[x][pow2];
        }
        return lifting[x][0];
    }

    ll dis(int x, int y) {
        ll p = lca(x,y);
        return sum[x] + sum[y] - 2*sum[p];
    }
}
set<ll> times;
set<ll> nodes;
ll head;
ll ans = 0;

bool func1(ll x) {
    auto it = times.lower_bound(LCA::in[x]);
    if (it == times.end()) return false;
    if (*it < LCA::in[x] + LCA::sz[x]) return true;
    return false;
}

bool func2(ll x) {
    ll a = *times.begin();
    ll b = *times.rbegin();
    if (a >= LCA::in[x] && b < LCA::in[x] + LCA::sz[x]) return true;
    return false;
}

void add(ll x) {
    if (nodes.empty()) {
        nodes.insert(x);
        times.insert(LCA::in[x]);
        head = x;
        return;
    }

    ll p = x;
    for (int pow2 = LCA::maxPow-1; pow2>=0; pow2--) {
        if (!func1(LCA::lifting[p][pow2])) p = LCA::lifting[p][pow2];
    }
    if (!func1(p)) p = LCA::lifting[p][0];
    ans += LCA::dis(p,x);
    if (LCA::in[p] < LCA::in[head]) {
        ans += LCA::dis(head, p);
        head = p;
    }

    nodes.insert(x);
    times.insert(LCA::in[x]);
}

void remove(ll x) {
    nodes.erase(x);
    times.erase(LCA::in[x]);
    if (nodes.empty()) return;

    ll p = x;
    for (int pow2 = LCA::maxPow-1; pow2>=0; pow2--) {
        if (!func1(LCA::lifting[p][pow2])) p = LCA::lifting[p][pow2];
    }
    if (!func1(p)) p = LCA::lifting[p][0];
    ans -= LCA::dis(x,p);

    ll nhead = *nodes.begin();
    for (int pow2 = LCA::maxPow-1; pow2>=0; pow2--) {
        if (!func2(LCA::lifting[nhead][pow2])) nhead = LCA::lifting[nhead][pow2];
    }
    if (!func2(nhead)) nhead = LCA::lifting[nhead][0];

    if (nhead == head) return;
    ans -= LCA::dis(head, nhead);
    head = nhead;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n; cin>>n; 
    for (int i=1; i<n; i++) {
        ll a,b,c; cin>>a>>b>>c; --a; --b;
        vadj[a].push_back({b,c});
        vadj[b].push_back({a,c});
    }
    LCA::build(0,0);

    ll q; cin>>q;
    while (q--) {
        char c; ll x; cin>>c>>x; 
        --x;
        if (c == '+') add(x);
        else remove(x);
        cout << ans << '\n';
    }
}

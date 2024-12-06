#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int mod = 1e9 + 7;
const int maxn = 2e5;

ll bin_exp(ll a, ll x) {
    ll ans = 1;
    while (x) {
        if (x%2) ans = (ans * a) % mod;
        x/=2;
        a = (a*a) % mod;
    }
    return ans;
}

namespace LCA{
    const int maxPow = 30; 
    int lifting[maxn][maxPow];
    int in[maxn];
    int out[maxn];
    int timeTransversal=0;

    void clear() {
        timeTransversal = 0;
    }

    void build (int x, int p, vector<vll>& vadj) {
        lifting[x][0] = p;
        in[x] = timeTransversal++;
        for (int i = 0; i < maxPow-1; i++) {
            lifting[x][i+1] = lifting[lifting[x][i]][i];
        }
        for (int y: vadj[x]) {
            if (y == p) continue;
            build(y, x, vadj);
        }
        out[x]= timeTransversal++;
    }

    bool isAncestor(int x, int y) {
        return (in[x] <= in[y] && out[x] >= out[y]);
    }

    int lca(int x, int y) {
        if (isAncestor(x,y)) return x;
        if(isAncestor(y,x)) return y;

        for(int pow2 = maxPow-1; pow2>=0; pow2--) {
            if (!isAncestor(lifting[x][pow2],y)) {
                x = lifting[x][pow2];
            }
        }
        return lifting[x][0];
    }
}


vector<pll> vadj[maxn];
vector<vll> v2;
ll d[maxn];
ll m[maxn];

void DFS(ll x, ll p, ll mult) {
    d[x] = d[p] + 1;
    m[x] = mult;
    for (pll v: vadj[x]) {
        if (v.first == p) continue;
        ll nm = (mult  * v.second) % mod;
        DFS(v.first, x, nm);
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    v2.resize(N);
    d[0] = 0;
    for (int i = 0; i < N-1; i++) {
        ll a, b, c; cin >> a >> b >> c; 
        a--; b--;
        vadj[a].push_back({b,c});
        vadj[b].push_back({a,c});
        v2[a].push_back(b);
        v2[b].push_back(a);
    }
    DFS(0, 0, 1);
    LCA::clear();
    LCA::build(0,0,v2);

    ll Q; cin >> Q;
    while (Q--) {
        ll a, b; cin >> a >> b;
        a--; b--;
        /*
        if (LCA::isAncestor(a,b)) {
            cout << ( m[b] * bin_exp(m[a], mod-2)) % mod << '\n';
            continue;
        }
        if (LCA::isAncestor(b,a)) {
            cout << (m[a] * bin_exp(m[b], mod-2)) % mod << '\n';
            continue;
        }
        */

        ll ans = (m[a] * m[b]) % mod;
        ll pp = LCA::lca(a,b); 
        ll div = bin_exp(m[pp], mod-2);
        div = (div * div) % mod;
        ans = (ans * div) % mod;
        cout << ans << '\n';
    }
}

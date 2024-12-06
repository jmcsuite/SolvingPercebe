#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxb = 29;
const int maxn = 2e5; 

struct trie {
    ll n; 
    vector<vector<int>> edg;
    vector<int> cc;

    void init() {
        edg.push_back({0, 0});
        cc.push_back(1);
        n = 1;
    }
    
    void add(ll x) {
        int c = 0;
        for (ll i = maxb; i >= 0; i--) {
            cc[c]++;
            ll b = (x & (1ll << i));
            b = (b == 0 ? 0 : 1);
            if (edg[c][b] != 0) {
                c = edg[c][b];
                continue;
            }
            else {
                edg[c][b] = n;
                c = n;
                edg.push_back({0,0});
                cc.push_back(0);
                n++;
            }
        }
        cc[c]++;
    }

    void rem(ll x) {
        int c = 0;
        for (ll i = maxb; i >= 0; i--) {
            cc[c]--;
            ll b = (x & (1ll << i));
            b = (b == 0 ? 0 : 1);
            c = edg[c][b];
        }
        cc[c]--;
    }

    ll sol(ll x) {
        ll ans = 0;
        int c = 0;
        for (ll i = maxb; i >= 0; i--) {
            ll b = (x & (1ll << i));
            b = (b == 0 ? 1 : 0);
            if (edg[c][b] != 0 && cc[edg[c][b]] > 0) {
                c = edg[c][b];
                ans |= (1ll << i);
                continue;
            }
            b++; b%= 2;
            c = edg[c][b];
        }
        return ans;
    }
};

ll dep[maxn];
ll xo[maxn];
vector<pll> vadj[maxn];

void DFS(ll x, ll p, ll d, ll val) {
    dep[x] = d;
    xo[x] = val;
    for (auto y : vadj[x]) {
        if (y.first == p) continue;
        DFS(y.first, x, d+1, val ^ y.second);
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, Q; cin >> N >> Q;
        for (int i = 0; i < N; i++) vadj[i].clear();
        for (int i = 0; i < N-1; i++) {
            ll a,b,c; cin >> a >> b >> c;
            a--; b--; 
            vadj[a].push_back({b,c});
            vadj[b].push_back({a,c});
        }
        DFS(0,0,0,0);
        ll qsum = 0;
        trie t1, t2;
        t1.init(); t2.init();
        for (int i = 0; i < N; i++) {
            if (dep[i]%2) t2.add(xo[i]);
            else t1.add(xo[i]);
        }

        while (Q--) {
            char a; cin >> a;
            if (a == '^') {
                ll b; cin >> b;
                qsum ^= b;
                continue;
            }
            ll b, x;
            cin >> b >> x; b--;
            ll to_sol = xo[b] ^ x; 
            if (dep[b] % 2) to_sol ^= qsum;

            if (dep[b] % 2) t2.rem(xo[b]);
            else t1.rem(xo[b]);

            ll a1 = t1.sol(to_sol);
            ll a2 = t2.sol(to_sol ^ qsum);

            if (dep[b] % 2) t2.add(xo[b]);
            else t1.add(xo[b]);
            cout << max(a1, a2) << ' ';
        }
        cout << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;

const int maxk = 32;
const int maxn = 100;

typedef struct edge {
    ll v;
    ll cap;
    ll f;
    struct edge* ret;
} edge;

ll INF = 1e9;


vector<edge*> vadj[maxk*maxn + 2];
int vis[maxk*maxn + 2];

void add_edge(ll v, ll u, ll c) {
    struct edge* ve = new edge();
    struct edge* ue = new edge();
    ve->ret = ue;
    ue->ret = ve;

    ve->v = u;
    ue->v = v;

    ve->cap = c;

    vadj[v].push_back(ve);
    vadj[u].push_back(ue);
}

ll flow(ll x, ll T, ll curr) {
   if (curr == 0) return 0;
   if (x == T) return curr; 
   if (vis[x]) return 0;
   vis[x] = 1;

   for (edge* e: vadj[x]) {
       ll r = flow(e->v, T, min(curr, e->cap - e->f));
       if (r == 0) continue;
       e->f += r;
       e->ret->f -= r;
       return r;
   }
   return 0;
}


ll ford(ll S, ll T, ll N) {
    ll ans = 0;
    while (1) {
        for (int i = 0; i < N; i++) vis[i] = 0;
        ll f = flow(S, T, INF);
        if (f == 0) return ans;
        ans += f;
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M; cin >> N >> M;

    map<pll, ll> mp;
    int S = 0; int T = 1;
    ll idx = 2;

    vector<vll> decomp;
    decomp.resize(N);
    for (int i = 0; i < N; i++) {
        ll x; cin >> x;
        for (ll j = 2; j*j <= x; j++) {
            if (x%j != 0) continue;
            ll cc = 0;
            while (x%j == 0) {
                cc++; x/=j;
            }
            pll t(i,j);
            mp[t] = idx;

            if (i % 2) add_edge(idx, T, cc);
            else add_edge(S, idx, cc);

            idx++;
            decomp[i].push_back(j);
        }
        if (x == 1) continue;
        decomp[i].push_back(x);
        pll t(i, x);
        mp[t] = idx;

        if (i % 2) add_edge(idx, T, 1);
        else add_edge(S, idx, 1);

        idx++;
    }

    for (int i = 0; i < M; i++) {
        ll a, b; cin >> a >> b;
        a--; b--;
        for (ll x : decomp[a]) {
            for (ll y : decomp[b]) {
                if (x != y) continue;
                pll ta(a, x);
                pll tb(b, x);
                ll v = mp[ta];
                ll u = mp[tb];
                if (a % 2) swap(v,u);
                add_edge(v, u, INF);
            }
        }
    }

    cout << ford(S, T, idx) << '\n';
}


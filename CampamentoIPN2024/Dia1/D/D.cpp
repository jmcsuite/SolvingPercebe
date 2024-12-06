#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;
using vpll = vector<pll>;

const int maxn = 50 * 101 + 2;
namespace MCMF {
    typedef struct edge {
        ll f; 
        ll cost;
        ll cap;
        ll v;
        struct edge* back;
        edge(ll _cost, ll _cap, ll _v) : 
            f(0), cost(_cost), cap(_cap), v(_v) {}
    } edge;
    const long long INF = 1e16;

    vector<edge*> vadj[maxn];

    void addEdge(ll u, ll v, ll cost, ll cap) {
        edge* a = new edge(cost, cap, v);
        edge* b = new edge(cost*-1, 0, u);
        a->back = b;
        b->back = a;
        vadj[u].push_back(a);
        vadj[v].push_back(b);
    }

    pll sendFlow(ll S, ll T, ll N) {
        vll vl(N, INF);
        vector<edge*> prev(N, NULL);
        queue<ll> q; q.push(S);
        vl[S] = 0;
        
        vll inQueue(N); 
        inQueue[S] = 1;
        while (!q.empty()) {
            int k = q.front(); q.pop();
            inQueue[k] = 0;
            for (edge* e : vadj[k]) {
                if (e->f == e->cap) continue;
                if (e->cost + vl[k] >= vl[e->v]) continue;
                vl[e->v] = e->cost + vl[k];
                prev[e->v] = e;
                if (inQueue[e->v]) continue;
                q.push(e->v);
                inQueue[e->v]=1;
            }
        }

        if (vl[T] == INF) return {0,0};
        ll f = INF;
        ll x = T;
        while (x != S) {
            f = min(prev[x]->cap - prev[x]->f, f);
            x = prev[x]->back->v;
        }
        x = T;
        while (x != S) {
            prev[x]->f += f;
            prev[x]->back->f -= f;
            x = prev[x]->back->v;
        }
        return {f, vl[T]};
    } 

    pll maxFlow(ll S, ll T, ll N) {
        pll ans {0,0};
        while (1) {
            pll x = sendFlow(S, T, N);
            if (x.first == 0) return ans;
            ans.first += x.first;
            ans.second += x.second * x.first;
        }
    }
}

inline int getNode(ll idx, ll t) {
    return (t * 50 + idx + 2);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M, K, C, D; cin >> N >> M >> K >> C >> D;
    ll S, T; S = 0; T = 1;

    vll vl(N);
    vll cc(K+1);
    for (int i = 1; i <= K; i++) cc[i] = (i*i - (i-1)*(i-1));

    for (int i = 0; i < K; i++) {
        ll x; cin >> x; x--;
        vl[x]++;
    }

    for (int i = 0; i < N; i++) {
        if (vl[i] == 0) continue;
        MCMF::addEdge(S, getNode(i, 0), 0, vl[i]);
    }

    for (int t = 1; t <= 100; t++) {
        MCMF::addEdge(getNode(0, t), T, t*C, MCMF::INF);
    }

    for (int i = 1; i < N; i++) {
        for (int j = 0; j < 100; j++) {
            MCMF::addEdge(getNode(i,j), getNode(i,j+1), 0, MCMF::INF);
        }
    }

    for (int i = 0; i < M; i++) {
        ll u, v; cin >> u >> v; u--; v--;
        for (int j = 0; j < 100; j++) {
            for (int k = 1; k <= K; k++) {
                MCMF::addEdge(getNode(u, j), getNode(v, j+1), cc[k]*D, 1);
                MCMF::addEdge(getNode(v, j), getNode(u, j+1), cc[k]*D, 1);
            }
        }
    }

    pll ans = MCMF::maxFlow(S, T, maxn);
    assert(ans.first == K);
    cout << ans.second << '\n';
}

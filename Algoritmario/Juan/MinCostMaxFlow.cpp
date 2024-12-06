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

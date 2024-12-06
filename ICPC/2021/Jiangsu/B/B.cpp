#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int inf = 1e9;
const int maxn = 1e4;
const int maxk = 8;
const int maxs = (1<<maxk);

ll dp[maxs][maxn];
ll ans[2][maxs];

vpll vadj[maxn];
vll ev[maxk][maxn];
vector<pair<ll,pll>> event;

void clear(ll n) {
    for (int i=0; i<n; i++) vadj[i].clear();
    for (int i=0; i<maxk; i++) for(int j=0; j<n; j++) ev[i][j].clear();
    for (int k=0; k<2; k++) for(int i=0; i<maxs; i++) ans[k][i] = inf;
    event.clear();
}

ll getNextX(ll k, ll v, ll x) {
    ll a = ev[k][v].size();
    ll dis = a;
    while (dis) {
        if (a - dis >= 0 && ev[k][v][a-dis] >= x) a-=dis;
        else dis/=2;
    }
    if (a == (ll)ev[k][v].size()) return inf;
    return ev[k][v][a];
}

ll N,M,K;
void solve() {
    cin >> N >> M >> K;
    clear(N);
    for (int i=0; i<M; i++) {
        ll a,b,w; cin>>a>>b>>w;
        a--; b--;
        vadj[a].push_back({b,w});
        vadj[b].push_back({a,w});
    }
    ll P,T; cin >> P >> T;
    event.resize(P);
    for (int i=0; i<P; i++) {
        cin >> event[i].second.first >> event[i].second.second >> event[i].first;
        --event[i].second.first; --event[i].second.second;
    }
    sort(event.begin(), event.end());
    for (int i=0; i<P; i++) {
        ev[event[i].second.first][event[i].second.second].push_back(event[i].first);
    }

    ll x, y;
    cin >> x >> y; --x; --y;

    for (int tt = 0; tt < 2; tt++) {
        for (int i=0; i<maxs; i++) for(int j=0; j<N; j++) dp[i][j] = inf;
        dp[0][x] = 0;
        swap(x,y);
        for (int k = 0; k < (1<<K); k++) {
            // first daikra
            set<pll> st;
            for (int i=0; i<N; i++) if(dp[k][i] != inf) st.insert({dp[k][i], i});
            while (!st.empty()) {
                ll u = st.begin()->second;
                ll d = st.begin()->first;
                st.erase(st.begin());
                if (dp[k][u] < d) continue;
                for (pll edge: vadj[u]) {
                    ll nd = edge.second + d;
                    if (dp[k][edge.first] <= nd) continue;
                    dp[k][edge.first] = nd;
                    st.insert({nd, edge.first});
                }
            }

            // then add to mask
            for (int i=0; i<N; i++) {
                for (int kill=0; kill<K; kill++) {
                    if ((k&(1<<kill)) == 1) continue;
                    dp[k|(1<<kill)][i] = min(dp[k|(1<<kill)][i], getNextX(kill, i, dp[k][i]));
                }
            }
            for (int i=0; i<N; i++) ans[tt][k] = min(ans[tt][k], dp[k][i]);
        }
    }

    ll res = inf;
    for (int k=0; k<(1<<K); k++) {
        res = min(res, max(ans[0][k], ans[1][(1<<K)-1-k]));
    }
    if (res > T) {
        cout << -1 << '\n';
        return;
    }
    cout << res << '\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}

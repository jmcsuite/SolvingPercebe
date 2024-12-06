#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
using vll = vector<ll>;

const int maxn = 4e5 + 2;
namespace Dinics{
    map<ll,ll> vadj[maxn];
    vpll layered[maxn];
    vpll layeredSum[maxn];
    int level[maxn];
    int index[maxn];
    const long long maxFlow = 1e16;

    void clear(int N) {
        for (int i = 0; i < N; i++) vadj[i].clear();
    }

    void buildLayered(int N, int S) {
        for (int i = 0; i < N; i++) level[i] = -1;
        queue<int> q;
        queue<int> q2;
        int step = 1;
        level[S] = 0;
        q.push(S);
        while (1) {
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for(pll yy : vadj[x]) {
                    int y = yy.first;
                    if (level[y] != -1) continue;
                    if (yy.second <= 0) continue;
                    level[y] = step;
                    q2.push(y);
                }
            }
            if (q2.empty()) break;
            step++;
            while(!q2.empty()) {
                q.push(q2.front());
                q2.pop();
            }
        }

        for (int i = 0; i < N; i++) {
            layered[i].clear();
            layeredSum[i].clear();
            for (pll yy:vadj[i]) {
                if (level[i]+1 != level[yy.first]) continue;
                layered[i].push_back(yy);
                layeredSum[i].push_back(yy);
            }
        }
    }

    ll blockFlow(int x, ll flow, int T) {
        if (flow == 0) return flow;
        if(x == T) return flow;
        if (index[x] >= (ll)layered[x].size()) return 0;
        for(size_t i=index[x]; i <layered[x].size(); index[x]++,i=index[x]) {
            ll nextFlow = min(flow,layered[x][i].second);
            ll attempt = blockFlow(layered[x][i].first, nextFlow, T);
            if (attempt != 0) {
                layered[x][i].second -= attempt;
                if(layered[x][i].second == 0) index[x]++;
                return attempt;
            }
        }
        return 0;
    }

    ll blockPaths(ll N, ll S, ll T) {
        for (int i = 0; i < N; i++) index[i] = 0;
        ll ans = 0;
        while (1) {
            ll flow = blockFlow(S, maxFlow, T);
            ans+= flow;
            if (flow == 0) return ans;
        }
    }

    ll dinics(ll N, ll S, ll T) {
        ll ans = 0;
        while (1) {
            buildLayered(N,S);
            ll push = blockPaths(N,S,T);
            ans+= push;
            if (push == 0) return ans;
            for (int i = 0; i < N; i++) {
                for (size_t j = 0; j < layered[i].size(); j++) {
                    vadj[i][layered[i][j].first] = layered[i][j].second;
                    vadj[layered[i][j].first][i] += layeredSum[i][j].second - layered[i][j].second;
                }
            }
        }
    }

    void minCover(ll N, ll S, ll T, vll& mc, ll n1, ll n2) {
        set<ll> minCut; 
        queue<ll> q;
        vll vis(N);
        q.push(S);
        while (!q.empty()) {
            ll x; x = q.front();
            q.pop();
            vis[x] = 1;
            minCut.insert(x);
            for (pll y : vadj[x]) {
                if (y.second == 0) continue;
                if (vis[y.first]) continue;
                q.push(y.first);
                vis[y.first] = 1;
            }
        }

        for (int i = 0; i < n1; i++) {
            if (minCut.find(i) != minCut.end()) continue;
            mc.push_back(i);
        }

        for (int i = n1; i < n1 + n2; i++) {
            if (minCut.find(i) == minCut.end()) continue;
            mc.push_back(i);
        }
    }
}


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N1, N2, M, Q; 
    cin >> N1 >> N2 >> M >> Q;
    ll S = N1 + N2;
    ll T = S+1;
    for (int i = 0; i < N1; i++) Dinics::vadj[S][i] = 1;
    for (int i = N1; i < N1 + N2; i++) Dinics::vadj[i][T] = 1;
    vpll edges;
    for (int i = 0; i < M; i++) {
        ll a,b; cin >> a >> b;
        a--; b--;
        Dinics::vadj[a][b+N1] = Dinics::maxFlow;
        edges.push_back({a, b+N1});
    }
    Dinics::dinics(N1+N2+2, S, T);
    vll mc;
    Dinics::minCover(N1+N2+2, S, T, mc, N1, N2);

    ll sum = 0;
    map<ll,ll> rm;
    set<ll> ans;
    for (int i = 0; i < M; i++) {
        if (Dinics::vadj[edges[i].first][edges[i].second] == Dinics::maxFlow) continue;
        ans.insert(i+1);
        sum += i+1;
        rm[edges[i].first] = i+1;
        rm[edges[i].second] = i+1;
    }

    ll i = 0;
    while (Q--) {
        int q; cin >> q;
        if (q == 1) {
            cout << 1 << '\n';
            cout << (mc[i] >= N1 ? (mc[i] + 1 - N1)*-1 : (mc[i]+1)) << '\n';
            sum -= rm[mc[i]];
            ans.erase(rm[mc[i]]);
            i++;
            cout << sum << endl;
            continue;
        }
        cout << ans.size() << '\n';
        for (auto it = ans.begin(); it != ans.end(); it++) {
            if (it != ans.begin()) cout << ' ';
            cout << *it;
        }
        cout << endl;
    }
}

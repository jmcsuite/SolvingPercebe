#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;

const int maxn = 1e5;
vll vadj[maxn];
ll t[maxn];
ll vl[maxn];
ll indegree[maxn];

void dijkstra() {
    for (int i = 0; i < maxn; i++) t[i] = 1e17;
    set<pll> st;
    st.insert({0,0});
    t[0] = 0;
    while (!st.empty()) {
        auto x = *st.begin();
        st.erase(st.begin());
        if (x.first != t[x.second]) continue;
        ll nt = vl[x.second] + t[x.second];
        for (int y : vadj[x.second]) {
            if (nt >= t[y]) continue;
            t[y] = nt;
            st.insert({nt, y});
        }
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M, K; cin >> N >> M >> K;
    if (N == 2 && K == 1) {
        cout << "impossible\n";
        return 0;
    }
    for (int i = 0; i < N; i++) cin >> vl[i];
    for (int i = 0; i < M; i++) {
        ll u, v; cin >> u >> v;
        u--; v--;
        vadj[u].push_back(v);
        vadj[v].push_back(u);
    }

    bool special = false;
    for (int y : vadj[0]) {
        if (y == N-1) special = true;
    }

    string ans; ans.resize(N);
    if (special) {
        if (K <= 1) ans[0] = ans[N-1] = 'S';
        else ans[0] = ans[N-1] = 'N';
        if (K > 1) K -= 2;
        for (int i = 1; i < N-1; i++, K--) ans[i] = (K > 0 ? 'N' : 'S');
        cout << ans << '\n';
        return 0;
    }

    dijkstra();
    for (int u = 0; u < N; u++) {
        for (int v : vadj[u]) {
            if (t[u] + vl[u] == t[v]) indegree[v]++;
        }
    }

    queue<int> q; 
    for (int i = 0; i < N; i++) if (indegree[i] == 0) q.push(i);
    while (!q.empty()) {
        int x = q.front(); q.pop();
        ans[x] = (K > 0 ? 'N' : 'S');
        K--;
        for (int v : vadj[x]) {
            if (t[x] + vl[x] != t[v]) continue;
            indegree[v]--;
            if (indegree[v] == 0) q.push(v);
        }
    }
    cout << ans << '\n';
}

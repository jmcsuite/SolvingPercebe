#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 1e5; 
ll disc[maxn], lo[maxn], sum[maxn];
vll vadj[maxn];

void clear(int N) {
    for (int i = 0; i < N; i++) {
        vadj[i].clear();
        disc[i] = -1;
        sum[i] = 0;
    }
}

ll ans = 0;
ll N, M;

pll DFS(ll x, ll p, ll d) {
    if (disc[x] != -1) return {disc[x], 0};

    lo[x] = disc[x] = d;
    sum[x] = 1;

    for (ll y : vadj[x]) {
        if (y == p) continue;
        pll son = DFS(y,x,d+1);
        sum[x] += son.second;
        lo[x] = min(son.first, lo[x]);

        if (lo[y] > disc[x]) ans = max(ans, sum[y] * (N-sum[y]));
    }

    return {lo[x], sum[x]};
}


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> N >> M;
        clear(N);
        for (int i = 0; i < M; i++) {
            ll a, b; cin >> a >> b;
            a--; b--;
            vadj[a].push_back(b);
            vadj[b].push_back(a);
        }
        ans = 0;
        DFS(0, 0, 0);
        cout << (N* (N-1))/2 - ans  << '\n';
    }
}

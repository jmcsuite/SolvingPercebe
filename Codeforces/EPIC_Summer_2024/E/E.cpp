#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 5001;
ll vl[maxn];
vll vadj[maxn];

ll k[maxn][maxn];
ll ans;
ll N;

ll inf = 1e15;

void clear(ll N) {
    for (int i = 0; i <= N; i++) vadj[i].clear();
    for (int i = 0; i <= N; i++) for (int j = 0; j <= N; j++) k[i][j] = 0;
    ans = 0;
}

void DFS(ll x, ll p) {
    ll sons = 0;
    ll s = 0;
    for (ll y : vadj[x]) {
        if (y == p) continue;
        DFS(y, x);
        sons++;
        s += vl[y];
    }
    if (sons == 0) {
        k[x][0] = inf;
        return;
    }

    for (ll y : vadj[x]) {
        for (int i = 1; i <= N; i++) {
            if (k[x][i] == inf) continue;
            if (k[y][i-1] == inf) k[x][i] = inf;
            else k[x][i] += k[y][i-1];
        }
    }

    ll delta = s - vl[x];
    ll pr = 1;
    while (delta < 0) {
        if (k[x][pr] == inf) {
            ans += delta * pr * -1;
            delta = 0;
        }
        else {
            ll mini = min(delta*-1, k[x][pr]);
            ans += mini * pr;
            delta += mini;
            k[x][pr] -= mini;
            pr++;
        }
    }
    k[x][0] = delta;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> N;
        clear(N);
        for (int i = 0; i < N; i++) cin >> vl[i];
        for (int i = 1; i < N; i++) {
            ll b; cin >> b; b--;
            vadj[i].push_back(b);
            vadj[b].push_back(i);
        }
        DFS(0,0);
        cout << ans << '\n';
    }
}

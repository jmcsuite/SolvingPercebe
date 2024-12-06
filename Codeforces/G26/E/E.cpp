#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 2e5;
vll vadj[maxn];
ll a[maxn];
ll b[maxn];
ll c[maxn];

void clear(ll N) {
    for (int i = 0; i < N; i++) vadj[i].clear();
}

void DFS(ll x, ll p) {
    a[x] = b[x] = 0;
    for (ll y : vadj[x]) {
        if (y == p) continue;
        DFS(y, x);
        a[x] += b[y];
        b[x] += max(a[y], b[y]);
    }
    a[x]++;
}

void D2(ll x, ll p) {
    if (x != p) {
        a[x] += b[p];
        b[x] += max(b[p], a[p]);
    }
    for (ll y : vadj[x]) {
        if (y == p) continue;
        ll sa = b[y];
        ll sb = max(a[y], b[y]);
        a[x] -= sa;
        b[x] -= sb;
        D2(y, x);
        a[x] += sa;
        b[x] += sb;
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0); ll T; cin >> T;
    while (T--) {
        ll N; cin >> N; clear(N);
        for (int i = 0; i < N-1; i++) {
            ll a,b; cin >> a >> b; a--; b--;
            vadj[a].push_back(b);
            vadj[b].push_back(a);
        }
        DFS(0,0);
        D2(0,0);
        ll ans = 0;
        for (int i = 0; i < N; i++) {
            ans = max(ans, b[i] + (vadj[i].size() == 1 ? 1 : 0));
        }
        cout << ans << '\n';
    }
}

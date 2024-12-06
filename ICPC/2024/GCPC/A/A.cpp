#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 2e5;

vll vadj[maxn];
ll vis[maxn];

ll DFS(ll x) {
    if (vis[x]) return 0;
    vis[x] = 1;
    ll ans = 1;
    for (ll y : vadj[x]) ans += DFS(y);
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin >> N >> M;
    for (int i = 0; i < M; i++) {
        ll a,b; cin >> a >> b;
        a--; b--;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }
    ll ans = 0;
    for (int i = 0; i < N; i++) ans = max(ans, DFS(i));
    cout << ans << '\n';
}

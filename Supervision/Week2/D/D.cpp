#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e5+1;

vll vadj[maxn];
ll depth[maxn];

void DFS(ll x, ll p) {
    depth[x] = depth[p]+1;
    for (ll y : vadj[x]) {
        if (y == p) continue;
        DFS(y,x);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (ll i=1; i<N; i++) {
        ll a,b; cin >> a >> b;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }
    DFS(1,1);
    double ans = 0;
    for (ll i=1; i<=N; i++) ans = ans + 1.0/depth[i];
    cout << fixed << setprecision(7);
    cout << ans << '\n';
}

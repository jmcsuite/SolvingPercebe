#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 100;
ll a[maxn];
ll b[maxn];

ll dp[maxn][maxn];
ll dp_kill[maxn][maxn];
ll T=0;

vll vadj[maxn];

ll calc_k(ll x, ll p) {
    if (dp_kill[x][p] != 0) return dp_kill[x][p];
    dp_kill[x][p] = b[x];
    for (ll y : vadj[x]) {
        if (y == p) continue;
        calc_k(y, x);
        dp_kill[x][p] += dp_kill[y][x];
    }
    return dp_kill[x][p];
}

ll calc(ll x, ll p) {
    if (dp[x][p] != 0) return dp[x][p];
    dp[x][p] = a[x];
    vpll ord; 

    for (ll y: vadj[x]) {
        if (y == p) continue;
        ll bv = calc_k(y,x);
        ll av = calc(y,x);
        ord.push_back({av-bv, y});
    }
    sort(ord.rbegin(), ord.rend());
    ll ans = 0;
    ll sum = 0;
    for (pll p: ord) {
        ans = max(ans, sum + calc(p.second, x));
        sum += calc_k(p.second, x);
    }
    return dp[x][p] = max(dp[x][p], ans + b[x]);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N;
    while(cin>>N, N) {
        for (ll i=0; i<N; i++) {
            vadj[i].clear();
            for (ll j=0; j<N; j++) dp[i][j]=dp_kill[i][j]=0;
        }

        for (ll i=0; i<N; i++) {
            ll x,y,z; cin >> x >> y >> z;
            y += z;
            x = max(x, y);
            a[i] = x;
            b[i] = y;
        }
        for (ll i=1; i<N; i++) {
            ll x,y; cin >> x >> y;
            --x; --y;
            vadj[x].push_back(y);
            vadj[y].push_back(x);
        }
        ll ans = calc(0,0);
        for (ll i=0; i<N; i++) ans = min(ans, calc(i,i));
        cout << "Case " << ++T << ": ";
        cout << ans << '\n';
    }
}

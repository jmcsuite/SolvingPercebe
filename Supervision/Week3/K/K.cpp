#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 1e3;
pll dp[maxn][2];
ll vis[maxn];
vll vadj[maxn];

void clear() {
    for (int i=0; i<maxn; i++) dp[i][0] = dp[i][1] = {-1, -1};
    for (int i=0; i<maxn; i++) vis[i]=0;
    for (int i=0; i<maxn; i++) vadj[i].clear();
}

void dfs(ll x, ll p) {
    vis[x]=1;
    for (ll y: vadj[x]) {
        if (y == p) continue;
        dfs(y,x);
    }
}

pll sol(ll x, ll p, ll s) {
    if (dp[x][s].first != -1) return dp[x][s];
    if (s == 0) {
        dp[x][s] = {1,1};
        for (ll y : vadj[x]) {
            if (y == p) continue;
            pll calc = sol(y,x,1);
            dp[x][s].first += calc.first;
            dp[x][s].second += calc.second;
        }
        return dp[x][s];
    }

    dp[x][s] = {1,0};
    for (ll y: vadj[x]) {
        if (y == p) continue;
        pll calc = sol(y,x,1);
        dp[x][s].first += calc.first;
        dp[x][s].second += calc.second;
    }

    pll option = {0,1};
    if (p == x) option.second--;
    for (ll y: vadj[x]) {
        if (y == p) continue;
        pll calc = sol(y,x,0);
        option.first += calc.first;
        option.second += calc.second;
    }

    return dp[x][s] = min(option, dp[x][s]);
}

void solve() {
    ll N,M; cin>>N>>M;
    clear();
    for (int i=0; i<M; i++) {
        ll a,b; cin>>a>>b;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }
    pll ans(0,0);
    for (int i=0; i<N; i++) {
        if (vis[i]) continue;
        dfs(i,i);
        pll calc = sol(i,i,1);
        ans.first += calc.first;
        ans.second += calc.second;
    }
    cout << ans.first << ' ' << M-ans.second << ' ' << ans.second <<'\n';
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--) solve();
}


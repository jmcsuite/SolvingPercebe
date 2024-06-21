#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 2e5;
ll dis[maxn]; 
vll vadj[maxn];

ll dp[maxn];

ll pre[2][maxn];

void calc(ll x, ll p) {
    ll ans = -1;
    for (ll y : vadj[x]) {
        if (y == p) continue;
        calc(y, x);
        ans = max(ans, dis[y]);
    }
    dis[x] = ++ans;
    return;
}

void solve(ll x, ll p) {
    multiset<ll> st;

    for (ll y: vadj[x]) {
        st.insert(dis[y]);
    }
    dp[x] = (st.empty() ? 0 : ((*st.rbegin()) + 1));

    for (ll y: vadj[x]) {
        if (y == p) continue;
        ll d = dis[y];
        st.erase(st.find(d));
        dis[x] = (st.empty() ? 0 : ((*st.rbegin()) + 1));
        solve(y, x);
        st.insert(d);
    }
}

void precalc(ll x, ll p, ll arr[maxn]) {
    for (ll y : vadj[x]) {
        if (y == p) continue;
        arr[y] = arr[x]+1;
        precalc(y, x, arr);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        for (int i = 0; i < N; i++) vadj[i].clear();
        ll r, b; cin >> r >> b; r--; b--;
        pre[0][r] = 0;
        pre[1][b] = 0;

        for (int i = 0; i < N-1; i++) {
            ll a, b; cin >> a >> b;
            a--; b--;
            vadj[a].push_back(b);
            vadj[b].push_back(a);
        }

        precalc(r, r, pre[0]);
        precalc(b, b, pre[1]);

        calc(0,0);
        solve(0,0);

        ll ans = 10*N;
        for (int i = 0; i < N; i++) {
            ll d = max(pre[0][i], pre[1][i]);
            if (d%2 != pre[1][i]%2) d++;
            ans = min(ans, d - dp[i] + 2*(N-1));
        }
        cout << ans << '\n';
    }
}

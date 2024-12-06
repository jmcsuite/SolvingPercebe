#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 2e5 + 1;

ll p[maxn], vl[maxn], s[maxn];
vector<ll> vadj[maxn];
set<pll> white;
set<pll> black;

void clear(ll N) {
    white.clear(); black.clear();
    for (int i = 0; i <= N; i++) vadj[i].clear();
}

void dfs(ll x, ll pp) {
    s[x] = 0;
    p[x] = pp;
    for (auto y : vadj[x]) {
        if (y == pp) continue;
        dfs(y, x);
        s[x] += vl[y];
    }

    if (vl[x] == 1) black.insert({s[x], x});
    else if (s[x] > 0) white.insert({s[x], x});
}

bool ans() {
    if (black.size() == 0) return false;
    if (black.size() == 1) return true;
    auto it = white.rbegin();

    if (it != white.rend()) {
        ll x = it->second;
        if (s[x] > 1) return false;
        it++;
    }

    if (it != white.rend() && s[it->second] >= 1) return false;

    auto i2 = black.rbegin();
    if (s[i2->second] > 2) return false;
    if (s[i2->second] == 2 && vl[p[i2->second]] != 0) return false;

    i2++;
    if (i2 != black.rend() && s[i2->second] >= 2) return false;
    return true;
}

void solve() {
    vl[0] = 0;
    ll N, Q; cin >> N >> Q;
    clear(N);
    for (int i = 1; i <= N; i++) cin >> vl[i];
    vadj[0].push_back(1);
    for (int i = 1; i < N; i++) {
        ll a, b; cin >> a >> b;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }

    dfs(0, 0);
    while (Q--) {
        ll x; cin >> x;

        if (vl[p[x]] == 1) black.erase({s[p[x]], p[x]});
        else white.erase({s[p[x]], p[x]});

        if (vl[x] == 1) {
            vl[x] = 0;
            black.erase({s[x], x});
            white.insert({s[x], x});
            s[p[x]]--;
        }
        else {
            vl[x] = 1;
            black.insert({s[x], x});
            white.erase({s[x], x});
            s[p[x]]++;
        }

        if (vl[p[x]] == 1) black.insert({s[p[x]], p[x]});
        else white.insert({s[p[x]], p[x]});

        cout << (ans() ? "Yes\n" : "No\n");
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;


void solve() {
    ll N, M; cin >> N >> M;

    vector<vll> vadj(N);
    vector<vll> op(N);
    vll end(M);
    vll deg(N);

    for (int i = 0; i < N; i++) {
        ll x; cin >> x;
        op[i].resize(x);
        for (int j = 0; j < x; j++) cin >> op[i][j];
        for (int j = 0; j < x; j++) {
            op[i][j]--;
            end[op[i][j]] = i;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j: op[i]) {
            if (end[j] == i) continue;
            deg[i]++;
            vadj[end[j]].push_back(i);
        }
    }

    queue<int> q;
    vll ans;
    for (int i = 0; i < N; i++) if (deg[i] == 0) q.push(i);
    while (!q.empty()) {
        ll x = q.front(); 
        q.pop();
        for (int y : vadj[x]) {
            deg[y]--;
            if (deg[y] == 0) q.push(y);
        }
        ans.push_back(x);
    }
    bool se = false;
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); i++) {
        if (ans[i] != i) se = true;
    }

    if (se == false || (int)ans.size() != N) {
        cout << "No\n";
    }
    else {
        cout << "Yes\n";
        for (int i = 0; i < (int)ans.size(); i++) {
            cout << ans[i]+1 << ((i+1) == (int)ans.size() ? '\n' : ' ');
        }
    }
}




int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        solve();
    }
}


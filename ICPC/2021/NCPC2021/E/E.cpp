#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

ll knapsack(vll& ww, ll C) {
    vll w;
    for (ll x : ww) {
        if (x > C) continue;
        if (x == 0) continue;
        w.push_back(x);
    }
    if (w.empty()) return 0;

    ll maxw = w[0];
    for (size_t i = 0; i < w.size(); i++) maxw = max(maxw, w[i]);
    vll dp(maxw*2 + 1, -1);
    vll prev(maxw*2 + 1, -1);
    auto xy = [=](ll x) {
        return (x-C+maxw);
    };

    size_t b = 0; ll sum = 0;
    for (size_t i = 0; i < w.size(); i++) {
        if (sum + w[i] > C) break;
        sum+=w[i]; b = i;
    }

    prev[xy(sum)] = b+1;
    for (size_t i = b+1; i < w.size(); i++) {
        for (ll j = C-maxw; j <= C + maxw; j++) dp[xy(j)] = prev[xy(j)];
        for (ll j = C-maxw; j <= C; j++) dp[xy(j+w[i])] = max(prev[xy(j)], dp[xy(j+w[i])]);
        for (ll j = C + maxw; j > C; j--) {
            for (ll k = dp[xy(j)]-1; k > prev[xy(j)]; k--) dp[xy(j-w[k])] = max(dp[xy(j-w[k])], k);
        }
        swap(prev, dp);
    }
    for (int i = C; i >= 0; i--) if (prev[xy(i)] != -1) return i;
    return -1;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, X; 
    cin >> N >> X;
    vll inp(N); 
    for (int i = 0; i < N; i++) cin >> inp[i];
    ll ans = 0;
    vll vl;
    for (int i = 0; i < N; i++) {
        ans = max(inp[i], ans);
        if (inp[i] > X) continue;
        vl.push_back(inp[i]);
    }
    sort(vl.begin(), vl.end());
    if (vl.size() <= 2) {
        cout << ans << '\n';
        return 0;
    }
    if (vl.size() <= 4) {
        cout << max(ans, X+1) << '\n';
        return 0;
    }
    vll w;
    for (int i = 4; i < (int)vl.size(); i++) w.push_back(X + 1 - vl[i]);
    ll s = 0; 
    for (int x : w) s += x;
    ll maxi = knapsack(w, s/2); 
    ans = max(ans, s - maxi + X + 1);
    cout << ans << '\n';
}

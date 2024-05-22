#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 1e4;
const int maxq = 1e5;

ll ans[maxq];
pair<pll,ll> q[maxq];
ll vl[maxn];
ll dp[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for (int i = 0; i < N; i++) cin>>vl[i];
    for (int i = 0; i < N; i++) dp[i] = 1e6;

    ll Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin>>q[i].first.first>>q[i].first.second;
        q[i].first.first--; q[i].first.second--;
        q[i].second = i;
    }

    /*
    assert(N <= 1e4);
    for (int i = 0; i < N; i++) assert(vl[i] > 0);
    for (int i = 0; i < N; i++) assert(vl[i] <= 1e6);
    assert(Q <= 1e5);
    */

    sort(q, q+Q, [](pair<pll,ll> a, pair<pll,ll> b) {
            ll a1 = a.first.second - a.first.first;
            ll b1 = b.first.second - b.first.first;
            if (a1 != b1) return a1 < b1;
            return a.first.first < b.first.first;
            });

    ll idx = 0;
    for (ll k = 1; k < N; k++) {
        for (int i = 0; i + k < N; i++) {
            dp[i] = min(dp[i], dp[i+1]);
            dp[i] = min(dp[i], abs(vl[i] - vl[i+k]));
            while (idx != Q && q[idx].first.first == i &&
                    q[idx].first.second == i+k) {
                ans[q[idx].second] = dp[i];
                idx++;
            }
        }
    }


    for (int i = 0; i < Q; i++) cout << ans[i] << '\n';
}

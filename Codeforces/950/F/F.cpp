#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, M, K; cin >> N >> M >> K;
        vector<pair<pll,ll>> vl(K);
        vector<ll> dp(K);
        for (int i = 0; i < K; i++) cin >> vl[i].first.first >> vl[i].first.second;
        for (int i = 0; i < K; i++) vl[i].second = i;
        sort(vl.begin(), vl.end(), [](pair<pll,ll> a, pair<pll,ll> b) {
                if (a.first.first != b.first.first) return a.first.first > b.first.first;
                return a.first.second < b.first.second;
                });

        ll ans = 0;
        ll dis = M; 
        ll j = N;
        for (int i = 0; i < K; i++) {
            ans += (j-vl[i].first.first) * dis;
            j = vl[i].first.first;
            ll ndis = min(dis, vl[i].first.second - 1);
            if (ndis == dis) dp[vl[i].second] = 0;
            else dp[vl[i].second] = 1;
            dis = ndis;
        }
        ans += j*dis;

        sort(vl.begin(), vl.end());

        vector<ll> maxi(K+1);
        maxi[K] = M+1;
        for (int i = K-1; i >= 0; i--) maxi[i] = min(maxi[i+1], vl[i].first.second);

        ll mimaxi = maxi[K];
        ll idx = -1;
        ll prev_row = N;
        for (int i = K-1; i >= 0; i--) {
            if (idx != -1) dp[vl[idx].second] += (mimaxi - vl[idx].first.second) *  (prev_row - vl[i].first.first);
            mimaxi = min(mimaxi, vl[i].first.second);
            prev_row = vl[i].first.first;
            if (dp[vl[i].second] != 0) {
                dp[vl[i].second] = 0; 
                mimaxi = maxi[i+1];
                idx = i;
            }
        }
        dp[vl[idx].second] += (mimaxi - vl[idx].first.second) * prev_row;

        cout << ans << '\n';
        for (int i = 0; i < K; i++) cout << dp[i] << (i == K-1 ? '\n' : ' ');
    }
}

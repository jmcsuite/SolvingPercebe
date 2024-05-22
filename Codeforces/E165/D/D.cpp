#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;

const int maxn = 2e5;
ll dp[maxn];
pll vl[maxn];
ll N, K;

void calc_dp() {
    for (int i = 0; i < N; i++) {
        dp[i] = max(0ll, vl[i].second - vl[i].first);
    }
    for (int i = 1; i < N; i++) dp[i] = dp[i] + dp[i-1];
}

ll get_sum(ll i) {
    if (i == 0) return dp[N-1];
    return dp[N-1] - dp[i-1];
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        cin >> N >> K;
        for (int i = 0; i < N; i++) cin >> vl[i].first;
        for (int i = 0; i < N; i++) cin >> vl[i].second;

        sort(vl, vl + N, [](pll a, pll b) { 
                if (a.second != b.second) return a.second > b.second;
                return a.first < b.first;
                });

        calc_dp();

        if (K == 0) {
            cout << dp[N-1] << '\n';
            continue;
        }

        ll ans, f;
        ans = f = 0;
        multiset<ll> st;
        for (int i = 0; i < K; i++) {
            f += vl[i].first;
            st.insert(vl[i].first);
        }

        for(int i = K; i <= N; i++) {
            ans = max(ans, get_sum(i) - f);
            if (i == N) continue;
            if (*st.rbegin() > vl[i].first) {
                f -= *st.rbegin();
                auto it = st.end(); 
                it--;
                st.erase(it);
                st.insert(vl[i].first);
                f += vl[i].first;
            }
        }

        cout << ans << '\n';
    }
}

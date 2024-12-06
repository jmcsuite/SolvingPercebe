#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vll = vector<ll>;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N,K; cin >> N >> K;
        vll vl(N);
        for (int i=0; i<N; i++) {
            char c; cin >> c;
            if (c == '1') vl[i]=1;
            else vl[i]=-1;
        }
        for (int i= N-2; i>=0; i--) vl[i] = vl[i] + vl[i+1];
        set<pll> st;
        for (int i=1; i<N; i++) st.insert({vl[i], i});

        ll sum = 0;
        ll ans = 1;
        for (auto it = st.rbegin(); it != st.rend(); it++) {
            if (it->first <= 0) break;
            sum += it->first;
            ans++;
            if (sum >= K) break;
        }

        if (sum >= K) cout << ans << '\n';
        else cout << -1 << '\n';
    }
}

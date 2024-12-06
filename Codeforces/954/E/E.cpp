#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
const int maxn = 1e5;

pll vl[maxn];
ll s1[maxn];
ll s2[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, K; cin >> N >> K;
        for (int i = 0; i < N; i++) {
            ll a; cin >> a;
            vl[i].first = a/K; vl[i].second = a%K;
        }

        sort(vl, vl+N, [](pll a, pll b) { 
                if (a.second != b.second) return a.second < b.second;
                return a.first < b.first;
                });

        for (int i = 0; i < N; i++) s1[i] = s2[i] = 0;

        for (int i = 1; i < N; i += 2) {
            if (vl[i].second != vl[i-1].second) s1[i] = -1;
            else s1[i] = vl[i].first - vl[i-1].first;
        }

        for (int i = N-2; i >= 0; i -= 2) {
            if (vl[i].second != vl[i+1].second) s2[i] = -1;
            else s2[i] = vl[i+1].first - vl[i].first;
        }

        for (int i = 1; i < N; i++) {
            if (s1[i] == -1 || s1[i-1] == -1) s1[i] = -1;
            else s1[i] = s1[i] + s1[i-1];
        }

        for (int i = N-2; i >= 0; i--) {
            if (s2[i] == -1 || s2[i+1] == -1) s2[i] = -1;
            else s2[i] = s2[i] + s2[i+1];
        }

        if (N%2 == 0) {
            cout << s1[N-1] << '\n';
            continue;
        }

        bool se = false;
        ll ans = 1e17;
        for (int i = 0; i < N; i += 2) {
            ll a1 = (i > 0 ? s1[i-1] : 0);
            ll a2 = (i < N-1 ? s2[i+1] : 0);
            ll a3 = ((a1 == -1 || a2 == -1) ? -1 : a1 + a2);
            if (a3 == -1) continue;
            ans = min(a3, ans);
            se = true;
        }
        if (se) cout << ans << '\n';
        else cout << -1 << '\n';
    }
}

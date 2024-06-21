#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5;
ll vl[maxn];
ll cc[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll H, N; cin >> H >> N;
        for (int i = 0; i < N; i++) cin >> vl[i];
        for (int i = 0; i < N; i++) cin >> cc[i];

        priority_queue<pair<ll,ll>> pq;
        for (int i = 0; i < N; i++) pq.push({0, i});
        ll ans = 0;
        while (H > 0) {
            auto q = pq.top(); pq.pop();
            ans = max(ans, q.first * -1);

            H -= vl[q.second];
            q.first -= cc[q.second];
            pq.push(q);
        }
        cout << ans+1 << '\n';
    }
}

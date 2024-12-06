#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6;
ll best[maxn+1];
ll my[maxn+1];

ll a[maxn];
ll b[maxn];
ll c[maxn];
ll inf = maxn + 2;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M; cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < N; i++) cin >> b[i];
    for (int i = 0; i < M; i++) cin >> c[i];

    //memset(best, inf, sizeof best);
    for (int i = 0; i <= maxn; i++) best[i] = inf;

    for (int i = 0; i < N; i++) {
        ll d = a[i] - b[i];
        best[a[i]] = min(d, best[a[i]]);
    }

    for (int i = 1; i <= maxn; i++) {
        best[i] = min(best[i-1], best[i]);
    }

    ll ans = 0;
    for (int i = 0; i < M; i++) {
        if (c[i] > maxn) {
            ll bb = best[maxn]; 
            ll dif = c[i] - maxn;
            ll k = dif / bb + ((dif%bb == 0) ? 0 : 1); //ceil
            ans += k*2;
            c[i] -= k * bb;
            assert(c[i] <= maxn);
        }
        my[c[i]]++;
    }

    for (int i = maxn; i >= 0; i--) {
        if (best[i] == inf) continue;
        ans += 2 * my[i];
        my[i - best[i]] += my[i];
    }
    cout << ans << '\n';
}


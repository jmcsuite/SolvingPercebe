#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5;

ll vl[maxn];
ll sum[maxn];

void s() {
    ll N, L, R; cin >> N >> L >> R;
    for (int i = 0; i < N; i++) cin >> vl[i];
    sum[0] = vl[0];
    for (int i = 1; i < N; i++) sum[i] = vl[i] + sum[i-1];

    ll ans = 0;
    ll i = 0;
    while (i < N) {
        ll prefix = 0;
        if (i > 0) prefix = sum[i-1];
        ll dis = N;
        ll x = N;
        while (dis) {
            if (x - dis >= i && sum[x-dis] - prefix >= L) x -= dis;
            else dis/= 2;
        }

        if (x == N) {
            i = i+1;
            continue;
        }

        if (sum[x] - prefix <= R) {
            ans++;
            i = x+1;
        }
        else {
            i = i+1;
        }
    }
    cout << ans << '\n';
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) s();
}

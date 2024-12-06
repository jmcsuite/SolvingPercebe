#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 2e5 + 1;
ll a[maxn];
ll b[maxn];

ll ab(ll x) {
    return (x < 0 ? x*-1 : x);
}

void solve() {
    ll N; cin >> N;
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i <= N; i++) cin >> b[i];

    ll x = b[N];
    ll delta = ab(b[N] - a[0]);
    ll ans = 0;

    for (int i = 0; i < N; i++) {
        if (a[i] < b[i]) swap(a[i], b[i]);
        if (x >= b[i] && x <= a[i]) delta = 0;
        delta = min(delta, ab(x - a[i]));
        delta = min(delta, ab(x - b[i]));
        ans += a[i] - b[i];
    }

    cout << ans + delta + 1 << '\n';
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}

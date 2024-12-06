#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const long long uno = 1;
const long long maxb = 60;

ll menor[maxb+1];
ll all[maxb+1];

ll DP(ll x, ll mb) {
    for (int i = 0; i <= maxb; i++) all[i] = menor[i] = 0;
    all[mb]=1;
    menor[mb] = (x&(uno<<mb) ? 1 : 0);

    for (int k = mb+1; k <= maxb; k++) {
        all[k] = 2*all[k-1];
        menor[k] = (x&(uno<<k) ? all[k-1] + menor[k-1] : menor[k-1]);
    }
    return menor[maxb];
}

ll ff(ll i) {
    return (i-uno)*(uno<<i)+1;
}

void solve() {
    ll N; cin >> N;
    N/=2;
    ll ans = 0;
    for (ll i = 0; i <= maxb; i++) ans += DP(N, i)*ff(i+1);
    cout << ans << '\n';
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) solve();
}

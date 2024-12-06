#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int mod = 1e9+7;

int main () {
    ll ans = 1;
    ll N; cin >> N;
    N++;
    for (int i = 2; i <= N; i++) {
        ans = (ans * 2 * (i-1)) % mod;
    }
    for (int i = N-1; i >= 1; i--) {
        ans = (ans * 2 * i) % mod;
    }
    cout << ans << '\n';
}

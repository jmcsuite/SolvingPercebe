#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll ans = 0;
    ll idx = 1; 
    ll N; cin >> N;
    N--;
    while (idx <= N) {
        ll cc = (N + idx) / (2*idx);
        ans += idx * cc;
        idx <<= 1;
    }
    cout << ans << '\n';
}

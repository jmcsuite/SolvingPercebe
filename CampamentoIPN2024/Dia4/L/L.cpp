#include <bits/stdc++.h>
using namespace std;
using ll = long long;
vector<ll> v = {2, 3, 5, 7, 37, 53, 23, 73, 373};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin >> N >> M;
    ll ans = 0;
    for (ll x: v) if (x <= M && x >= N) ans++;
    cout << ans << '\n';
}

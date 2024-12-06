#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    vll vl(N); vll a(N);
    for (int i = 0; i < N; i++) cin >> vl[i];
    for (int i = 0; i < N; i++) a[i] = vl[i]-i;
    sort(a.begin(), a.end());

    ll x = a[(N-1)/2];
    ll ans = 0;
    for (int i = 0; i < N; i++) ans = (ans + abs(x + i - vl[i]));
    cout << ans << '\n';
}

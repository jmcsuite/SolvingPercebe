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

    auto f = [&](int x) {
        ll ans = 0;
        for (int i = 0; i < N; i++) ans += abs(x-a[i]);
        return ans;
    };

    ll dis = 4e5;
    ll ans = dis + 1;
    while (dis) {
        ll fx = f(ans - dis);
        ll fy = f(ans - dis + 1);
        if (fx < fy) ans -= dis;
        else dis /= 2;
    }

    cout << f(ans) << '\n';
}

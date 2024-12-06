#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 1e5;

vll vadj[maxn];
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, H; cin >> N >> H;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < 3; j++) {
            ll x; cin >> x; vadj[i].push_back(x);
        }
        sort(vadj[i].rbegin(), vadj[i].rend());
    }

    ll ans = 0;
    for (int i = 0; i < N; i++) {
        if (vadj[i][2] > H) {
            cout << "impossible\n";
            return 0;
        }
        if (vadj[i][1] > H) ans += vadj[i][1];
        else ans += vadj[i][2];
    }
    cout << ans << '\n';
    return 0;
}


#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

struct w{
    ll p,l,a;
    w() : p(0), l(0), a(0) {}
};
const int maxn = 4000;
w vl[maxn];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, W; cin >> N >> W;
    for (int i = 0; i < N; i++) {
        char c; cin >> c;
        if (c == '!') {
            cin >> vl[i].p >> vl[i].l >> vl[i].a;
            continue;
        }

        ll q; cin >> q;
        ll ans = 0;
        for (int j = 0; j < N; j++) {
            if (vl[j].a == 0) continue;
            if (vl[j].p > q || q >= vl[j].p + vl[j].l) continue;
            ll m = (q - vl[j].p)%4;
            if (m == 1 || m == 3) continue;
            ans += (m == 0 ? vl[j].a : vl[j].a*-1);
        }
        cout << ans << '\n';
    }
}

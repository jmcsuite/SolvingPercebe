#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    if (b == 0) return a;
    return gcd(b%a, a);
}

vector<vll> divs() {
    const int maxn = 5e5+1;
    vector<vll> divs(maxn);

    for (int i = 1; i <= maxn; i++) {
        for (int j = 1; j * i <= maxn; j++) {
            divs[i*j].push_back(i);
        }
    }

    return divs;
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    vector<vll> div = divs();

    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        vll vl(N);
        for (int i = 0; i < N; i++) cin >> vl[i];
        vector<vll> ii(N+1);
        vector<vll> v(N+1);

        for (int i = 0; i < N; i++) {
            ll d = gcd(vl[i], i+1);
            ll ip = (i+1) / d;
            ll vp = (vl[i]) / d;
            ii[vp].push_back(ip);
            v[ip].push_back(vp);
        }

        vector<pll> vp(N+1);
        ll ans = 0;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j * i <= N; j++) {
                for (int jp : ii[j*i]) {
                    if (vp[jp].first == i) vp[jp].second++;
                    else vp[jp] = {i, 1};
                }
            }

            vp[i].second--;
            for (int y : v[i]) {
                for (int j : div[y]) {
                    if (vp[j].first == i) ans += vp[j].second;
                }
            }
        }
        cout << ans/2 << '\n';
    }
}

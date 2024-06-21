#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using pp = pair<pll, ll>;
using vll = vector<pp>;

ll bin(ll d, ll s, vll& vl) {
    ll N = vl.size();
    ll dis = N;
    ll x = -1;
    while (dis) {
        if ((dis + x < N) && (vl[dis+x].first.first <= d) && (vl[dis+x].first.first < d || vl[dis+x].first.second <= s)) x += dis;
        else dis /= 2;
    }
    return x; 
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, D; cin >> N >> D;
        vector<pll> vl(N); for (int i = 0; i < N; i++) cin >> vl[i].first >> vl[i].second;
        vll a(N); vll b(N);
        for (int i = 0; i < N; i++) {
            a[i] = {{vl[i].first - vl[i].second, vl[i].first}, i};
            b[i] = {{vl[i].first + vl[i].second, vl[i].first}, i};
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        ll a1, b1, c1;
        a1 = b1 = c1 = -1;
        for (int i = 0; i < N; i++) {
            // x-y; 
            ll j = bin(vl[i].first - vl[i].second, vl[i].first + D/2, a);
            if (j == -1) continue;
            if (a[j].first.first != vl[i].first - vl[i].second) continue;
            if (a[j].first.second != vl[i].first + D/2) continue;
            ll k = bin(vl[i].first - vl[i].second + D, vl[i].first + D, a);
            if (k != -1 && a[k].first.first == vl[i].first - vl[i].second + D && a[k].first.second >= vl[i].first + D/2) {
                a1 = i;
                b1 = a[j].second;
                c1 = a[k].second;
            }
            k = bin(vl[i].first - vl[i].second - D, vl[i].first, a);
            if (k != -1&& a[k].first.first == vl[i].first - vl[i].second - D && a[k].first.second >= vl[i].first - D/2) {
                a1 = i;
                b1 = a[j].second;
                c1 = a[k].second;
            }
        }

        for (int i = 0; i < N; i++) {
            ll j = bin(vl[i].first + vl[i].second, vl[i].first + D/2, b);
            if (j == -1) continue;
            if (b[j].first.first != vl[i].first + vl[i].second) continue;
            if (b[j].first.second != vl[i].first + D/2) continue;
            ll k = bin(vl[i].first + vl[i].second + D, vl[i].first + D, b);
            if (k != -1 && b[k].first.first == vl[i].first + vl[i].second + D && b[k].first.second >= vl[i].first + D/2) {
                a1 = i;
                b1 = b[j].second;
                c1 = b[k].second;
            }
            k = bin(vl[i].first + vl[i].second - D, vl[i].first, b);
            if (k != -1&& b[k].first.first == vl[i].first + vl[i].second - D && b[k].first.second >= vl[i].first - D/2) {
                a1 = i;
                b1 = b[j].second;
                c1 = b[k].second;
            }
        }
        cout << a1 + 1 << ' ' << b1 + 1 << ' ' << c1 + 1 << '\n';
    }
}

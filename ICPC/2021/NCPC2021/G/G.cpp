#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int f = 100;
struct circle {
    ll x, y, r; 
    circle() : x(0), y(0), r(0) {}
};

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    vector<circle> vl(N);
    for (int i = 0; i < N; i++) cin >> vl[i].x >> vl[i].y >> vl[i].r;
    for (int i = 0; i < N; i++) {
        vl[i].x *= f;
        vl[i].y *= f;
        vl[i].r *= f;
    }

    ll ans = 0;
    for (ll i = -1000; i < 2000; i++) {
        for (ll j = -1000; j < 2000; j++) {
            for (ll k = 0; k < N; k++) {
                ll dx = vl[k].x - i;
                ll dy = vl[k].y - j;
                if (dx * dx + dy * dy <= vl[k].r * vl[k].r) {
                    ans++;
                    break;
                }
            }
        }
    }

    cout << fixed << setprecision(6) << double(ans) / double(f*f) << '\n';
}

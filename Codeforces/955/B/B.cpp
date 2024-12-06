#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void s() {
    ll x, y, k; cin >> x >> y >> k;
    while (1) {
        if (k < y - (x%y)) {
            x += k;
            cout << x << '\n';
            return;
        }

        if (x == 1) {
            k = k%(y-1);
            continue;
        }

        ll delta = y - (x%y);
        k -= delta;
        x += delta;
        while (x%y == 0) x/=y;
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) s();
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxi = 1e3+1;

ll N;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;
    ll Q; cin >> Q;
    while (Q--) {
        ll S, P; cin >> S >> P;
        ll maxj = N/P;

        if (S%P) {
            S = S/P + 1;
        }
        else {
            S = S/P;
        }

        ll ans = 0;
        for (int i = 2; i <= maxi; i++) {
            ll x = S - ((i)*(i+1))/2;
            x = max(x, 0LL);
            if (x%i) { 
                x = x/i + 2;
            }
            else {
                x = x/i + 1;
            }
            x = max(1LL, x); 
            ll r = maxj-i+1;
            if (r >= x) ans = ans + r - x + 1;
        }
        cout << ans << '\n';
    }
}

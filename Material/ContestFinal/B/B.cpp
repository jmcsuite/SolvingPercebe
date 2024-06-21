#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        ll ans = 0;
        ll mans = 0;
        for (int i = 2; i <= N; i++) {
            ll suma = 0;
            for (int k = 1; k*i <= N; k++) {
                suma += k*i;
            }
            if (suma > ans) {
                ans = suma;
                mans = i;
            }
        }
        cout << mans << '\n';
    }
}

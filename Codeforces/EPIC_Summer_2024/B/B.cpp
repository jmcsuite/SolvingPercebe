#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 1e5;

ll vl[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N;
        for (int i = 0; i < N; i++) cin >> vl[i];
        ll sum = 0;
        ll maxi = vl[0];
        ll delta = 0;
        for (int i = 1 ; i < N; i++) {
            if (vl[i] < maxi) {
                sum += maxi - vl[i];
                delta = max(delta, maxi - vl[i]);
            }
            maxi = max(vl[i], maxi);
        }
        cout << sum + delta << '\n';
    }
}

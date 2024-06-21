#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N; cin >> N; 
        ll maxi = 0; 
        for (int i = 0; i < N-1; i++) {
            ll a; cin >> a;
            maxi = max(a, maxi);
        }
        ll b; cin >> b;
        cout << maxi + b << '\n';
    }
}

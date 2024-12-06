#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, F, K; cin >> N >> F >> K;
        vector<ll> vl(N);
        for (int i = 0; i < N; i++) cin >> vl[i];
        F = vl[F-1];
        sort(vl.rbegin(), vl.rend());
        ll fi, la; 
        for (int i = 0; i < N; i++) if (vl[i] == F) la = i;
        for (int i = N-1; i >= 0; i--) if (vl[i] == F) fi = i;

        if (K <= fi) {
            cout << "NO\n";
            continue;
        }
        if (K > la) {
            cout << "YES\n"; 
            continue;
        }
        cout << "MAYBE\n";
    }
}

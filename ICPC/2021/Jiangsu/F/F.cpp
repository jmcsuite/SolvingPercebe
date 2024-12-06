#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll getXor(ll m) {
    if (m == 1) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T; 
    while (T--) {
        ll M,N; cin >> M >> N;
        if (getXor(M) == N) cout << (1ll << M) << '\n';
        else cout << (1ll << M)-1 << '\n';
    }
}

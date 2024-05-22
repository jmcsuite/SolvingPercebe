#include <bits/stdc++.h>
using namespace std;
using ll  = long long;

ll T, N, K;

bool check(ll M) {
    ll idx = 1;
    for (int i = 0; i < K; i++) {
        if (idx > N) return false;
        cout << "? " << idx << " " << M << endl;
        cin >> idx;
        idx++;
    }
    if (idx != N+1) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> T;
    while (T--) {
        cin >> N >> K;
        ll ai = N;
        for (ll i = 1; i <= N; i++) {
            cout << "? 1 " << N*i << endl;
            ll x; cin >> x;
            if (x == N) ai = i;
        }

        ll ans = -1;
        for (ll j = 1; j*K <= N; j++) {
           if(check(j*ai)) ans = max(ans, j*ai);
        }
        cout << "! " << ans << endl;
        ll x; cin >> x;
        if (x == -1) return 0;
    }
}

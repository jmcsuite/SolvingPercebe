#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while(T--) {
        ll A,B,C; cin >> A >> B >> C;
        bool ans = false;
        for (int i = -100; i <= 100; i++) {
            for (int j = i+1; j <= 100; j++) {
                for (int k = j+1; k <= 100; k++) {
                    if ( (i+j+k) == A && (i*j*k) == B && (i*i + j*j + k*k) == C) {
                        cout << i << ' ' << j << ' ' << k << '\n';
                        ans = true;
                        break;
                    }
                }
                if (ans) break;
            }
            if (ans) break;
        }
        if (!ans) cout << "No solution.\n";
    }
}

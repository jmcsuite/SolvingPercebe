#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, M, X; cin >> N >> M >> X;
        if (X % M != 0) {
            cout << "S ";
            for (int i = 0; i < N; i++) {
                cout << M << (i == N-1 ? '\n': ' ');
            }
            continue;
        }

        if (M >= 3 && X%3 != 0) {
            cout << "S ";
            for (int i = 0; i < N; i++) {
                cout << 3 << (i == N-1 ? '\n': ' ');
            }
            continue;
        }


        if (M >= 3 && X >= 4) {
            ll pp = X/3;
            cout << "S ";
            for (int i = 1; i <= N; i++) {
                cout << (i % pp ? 3 : 2) << (i == N ? '\n' : ' ');
            }
            continue;
        }

        if (M <= 2) {
            if (N >= X) {
                cout << "N\n";
                continue;
            }
            cout << "S ";
            for (int i = 0; i < N; i++) {
                cout << 1 << (i == N-1 ? '\n' : ' ');
            }
            continue;
        }

        cout << "S ";
        if (X == 3) {
            for (int i = 0; i < N; i++) {
                cout << 2 << (i == N-1 ? '\n' : ' ');
            }
            continue;
        }

        while (1) {
        }
    }
}

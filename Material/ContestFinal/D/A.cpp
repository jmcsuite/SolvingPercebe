#include <bits/stdc++.h>
using namespace std;
using ll = long long;


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, M; cin >> N >> M;
        vector<vector<ll>> vl(N, vector<ll>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                char c; cin >> c;
                vl[i][j] = (c == '#' ? 1 : 0);
            }
        }

        ll c = -1;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (vl[i][j] == 1) c = j;
            }
            if (c != -1) break;
        }

        ll d = -1;
        for (int j = 0; j < M; j++) {
            for (int i = 0; i < N; i++) {
                if (vl[i][j] == 1) d = i;
            }
            if (d != -1) break;
        }
        cout << d+1 << ' ' << c+1 << '\n';
    }
}

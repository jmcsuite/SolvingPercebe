#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 100;
ll vl[maxn][maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T;
    while (T--) {
        ll N, M; cin >> N >> M;
        for(int i = 0; i < N; i++) for (int j = 0; j < M; j++) cin >> vl[i][j];

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                ll x = 0;
                if (i > 0) x = max(x, vl[i-1][j]);
                if (j > 0) x = max(x, vl[i][j-1]);
                if (j < M-1) x = max(x, vl[i][j+1]);
                if (i < N-1) x = max(x, vl[i+1][j]);
                if (x < vl[i][j]) vl[i][j] = x;
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cout << vl[i][j] << ' ';
            }
            cout << '\n';
        }
    }
}

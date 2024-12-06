#include <bits/stdc++.h>
using namespace std;
const int maxnm = 2e5;
using ll = long long;

ll row[maxnm];
ll col[maxnm];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin >> T; 
    while (T--) {
        ll N, M; cin >> N >> M;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                ll a; cin >> a; a--;
                row[a] = i; col[a] = j;
            }
        }

        vector<vector<ll>> ma(N, vector<ll>(M));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                cin >> ma[i][j];
                ma[i][j]--;
            }
        }

        bool se = true;
        for (int i = 0; i < N; i++) {
            for (int j = 1; j < M; j++) {
                if (row[ma[i][j]] != row[ma[i][j-1]]) se = false;
            }
        }

        for (int j = 0; j < M; j++) {
            for (int i = 1; i < N; i++) {
                if (col[ma[i][j]] != col[ma[i-1][j]]) se = false;
            }
        }
        cout << (se ? "YES\n" : "nO\n");
    }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 15;
bool board[maxn][maxn];

ll N;
ll T;
ll ans;
void queens(int x, int rw, int l, int r) {
    if (x == N) {
        ans++;
        return;
    }

    for (int i = 0; i < N; i++) {
        if (board[x][i]) continue;
        if ((rw & (1<<i)) | (l & (1<<i)) | (r & (1<<i))) continue;
        queens(x+1, rw | (1<<i), (l | (1<<i)) << 1, (r | (1<<i)) >> 1);
    }
}

int main () {
    while (cin >> N, N) {
        ans = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char c; cin >> c;
                board[i][j] = false;
                if (c == '.') continue;
                board[i][j] = true;
            }
        }

        queens(0, 0, 0, 0);
        cout << "Case " << ++T << ": " << ans << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 15;
bool board[maxn][maxn];

ll N;
ll T;
ll ans;
int rw, l, r;
void queens(int x) {
    if (x == N) {
        ans++;
        return;
    }

    for (int i = 0; i < N; i++) {
        if (board[x][i]) continue;
        if ((rw & (1<<i)) | (l & (1<<i)) | (r & (1<<i))) continue;
        int a,b,c;

        a = rw;
        b = l;
        c = r;

        rw = rw | (1<<i);
        l = (l | (1<<i)) << 1;
        r = (r | (1<<i)) >> 1;
        queens(x+1);

        rw = a;
        l = b;
        r = c;
    }
}

int main () {
    while (cin >> N, N) {
        ans = rw = l = r = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                char c; cin >> c;
                board[i][j] = false;
                if (c == '.') continue;
                board[i][j] = true;
            }
        }

        queens(0);
        cout << "Case " << ++T << ": " << ans << '\n';
    }
}

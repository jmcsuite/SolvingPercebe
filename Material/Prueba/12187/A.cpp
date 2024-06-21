#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 100;
ll vl[maxn][maxn];
ll tmp[maxn][maxn];

ll N, R, C, K;

ll dx[4] = {0, 1, 0, -1};
ll dy[4] = {1, 0, -1, 0};

void app(ll i, ll j) {
    tmp[i][j] = vl[i][j];
    for (int k = 0; k < 4; k++) {
        ll ni = i + dx[k];
        ll nj = j + dy[k];
        if (ni < 0 || ni >= R) continue;
        if (nj < 0 || nj >= C) continue;
        if (((vl[ni][nj] + 1) % N) == vl[i][j]) tmp[i][j] = vl[ni][nj];
    }
}

void it() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            app(i,j);
        }
    }
    swap(tmp, vl);
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(cin>>N>>R>>C>>K && (N || R || C || K)) {
        for (int i = 0; i < R; i++) for(int j = 0; j < C; j++) cin >> vl[i][j];
        while (K--) it();
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                cout << vl[i][j] << (j == C-1 ? '\n' : ' ');
            }
        }
    }
}

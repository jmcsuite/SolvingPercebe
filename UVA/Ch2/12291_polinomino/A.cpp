#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn = 10;
ll N,M;
ll a[maxn][maxn];
ll b[maxn][maxn];
ll vis[maxn][maxn];

bool ans;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

void DFS(ll i, ll j, ll x, ll y) {
    if (vis[x][y]) return;
    if (b[x][y] == 0) return;

    vis[x][y] = 1;
    if (i < 0 || i >= N || j < 0 || j >= N) {
        ans = false;
        return;
    }
    a[i][j]--;

    for (int k = 0; k < 4; k++) {
        ll nx = x + dx[k];
        ll ny = y + dy[k];
        ll ni = i + dx[k];
        ll nj = j + dy[k];
        if (nx < 0 || nx == M) continue;
        if (ny < 0 || ny == M) continue;
        DFS(ni, nj, nx, ny);
    }
}


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    while (cin >> N >> M && ( N || M)) {
        if (N  == 0) return -1;
        if (M == 0) return -1;
        for (int i = 0; i < N; i++) {
            for (int j = 0 ; j < N; j++) {
                char c; cin >> c;
                a[i][j] = (c == '*' ? 1 : 0);
            }
        }

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < M; j++) {
                char c; cin >> c;
                b[i][j] = (c == '*' ? 1 : 0);
            }
        }

        /*if (T == 156) {
            cout << N << ' ' << M << endl;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    cout << (a[i][j] ? '*' : '.');
                }
                cout << endl;
            }
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < M; j++) {
                    cout << (b[i][j] ? '*' : '.');
                }
                cout << endl;
            }
        }*/

        ans = true;
        for (int k = 0; k < 2; k++) {
            ll maxx, maxy; maxx = maxy = 0;
            for (int i = 0; i < M; i++) {
                for (int j = 0; j < M; j++){
                    if (b[i][j]) {
                        maxx = i;
                        maxy = j;
                    }
                }
            }

            ll maxi , maxj; maxi = maxj = 0;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (a[i][j] == 1) {
                        maxi = i;
                        maxj = j;
                    }
                }
            }
            //DFS(maxi, maxj, maxx, maxy);


            for (int x = 0; x < M; x++) {
                for (int y = 0; y < M; y++) {
                    ll i = x - maxx + maxi;
                    ll j = y - maxy + maxj;
                    if (i < 0 || i >= N || j < 0 || j >= N) {
                        if (b[x][y]) ans = false;
                        continue;
                    }
                    a[i][j] -= b[x][y];
                }
            }
        }
        //cout << ans << endl;

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (a[i][j] != 0) ans = false;
            }
        }

        cout << (ans ? 1 : 0) << '\n';
    }
}

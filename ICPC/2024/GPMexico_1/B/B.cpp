#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

const int maxn = 10;
using ll = long long;

ll B[maxn][maxn];
ll C[maxn][maxn];
ll X[maxn][maxn];
ll A[maxn][maxn] = {{0, 0, 3, 0, 3, 0, 3, 0, 3, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}};
    


void mult(ll N, ll A[maxn][maxn], ll B[maxn][maxn], ll X[maxn][maxn]){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ll x = 0;
            for (int k = 0; k < N; k++) x = (x + A[i][k]*B[k][j])%mod;
            X[i][j] = x;
        }
    }
}

void exp(ll x, ll N) {
    for (int i = 0; i < N; i++) for(int j = 0; j < N; j++) X[i][j] = 0;
    for (int i = 0; i < N; i++) for(int j = 0; j < N; j++) C[i][j] = A[i][j];
    for (int i = 0; i < N; i++) X[i][i] = 1;

    while(x) {
        if (x%2) {
            swap(X, B);
            mult(N, C, B, X);
        }
        x/=2;
        mult(N, C, C, B);
        swap(C, B);
    }
}
const int N = 10;

int main () {
    ios::sync_with_stdio(0);
    cin. tie(0);
    ll T; cin >> T;
    while (T--) {
        ll x; cin >> x; x/=2;
        exp(x, N);
        ll ans = 0;
        for (int i = 0; i < N; i++) ans = (ans + X[i][0])%mod;
        ans = (ans%mod + mod)%mod;
        cout << ans << '\n';
        /*
        cout << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) cout << X[i][j] << ' ';
            cout << endl;
        }
        */
    }
}

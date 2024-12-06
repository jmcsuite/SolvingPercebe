#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace Gauss {
    const int maxn = 1<<6;
    double mat[maxn][maxn+1];
    double ans[maxn];

    void Gauss(int N) {
        for (int i = 0; i < N-1; i++) {
            int l = i;
            for (int j = i+1; j < N; j++) {
                if (fabs(mat[j][i]) > fabs(mat[l][i])) l = j;
            }

            for (int k = i; k <= N; k++) swap(mat[i][k], mat[l][k]);
            for (int j = i+1; j < N; j++) {
                for (int k = N; k >= i; k--) {
                    mat[j][k] -= mat[i][k] * mat[j][i] / mat[i][i];
                }
            }
        }

        for (int i = N-1; i >= 0; i--) {
            double t = 0;
            for (int k = i+1; k < N; k++) {
                t += mat[i][k] * ans[k];
            }
            ans[i] = (mat[i][N] - t) / mat[i][i];
        }
    }
}

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,K; double p; cin >> N >> K >> p;

    int mask = (1<<N) - 1;
    for (int i = 0; i < (1<<N); i++) {
        if (__builtin_popcount(i) >= K) {
            Gauss::mat[i][(1<<N)] = 0;
            Gauss::mat[i][i] = 1;
            continue;
        }
        Gauss::mat[i][(1<<N)] = 1;
        Gauss::mat[i][i] = 1;
        Gauss::mat[i][(i<<1)&mask] -= (1-p);
        Gauss::mat[i][((i<<1)|1)&mask] -= p;
    }
    Gauss::Gauss(1<<N);
    cout << fixed << setprecision(7) << Gauss::ans[0] << '\n';
}

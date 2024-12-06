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

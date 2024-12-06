#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

char a3[5][3] = {{'V', 'V', 'V'}, {'V', 'Z', 'Z'}, {'V', 'Z', 'V'}, {'Z', 'Z', 'V'}, {'V', 'V', 'V'}};
char b3[5][3] = {{'U', 'U', 'U'}, {'U', 'X', 'U'}, {'X', 'X', 'X'}, {'U', 'X', 'U'}, {'U', 'U', 'U'}};

char four[5][4] = {{'P', 'T', 'T', 'T'}, {'P', 'P', 'T', 'V'}, {'P', 'P', 'T', 'V'}, {'L', 'V', 'V', 'V'}, {'L', 'L', 'L', 'L'}};
char cinco[5][5] = {{'I', 'I', 'I', 'I', 'I'}, {'L', 'L', 'P', 'P', 'P'}, {'L', 'V', 'P', 'P', 'T'}, {'L', 'V', 'T', 'T', 'T'}, {'L', 'V', 'V', 'V', 'T'}};

char diez[10][2] = {{'L', 'L'}, {'L', 'I'}, {'L', 'I'}, {'L', 'I'}, {'N', 'I'}, {'N', 'I'}, {'N', 'N'}, {'P', 'N'}, {'P', 'P'}, {'P', 'P'}};
char quince[15][2] = {{'L', 'L'}, {'L', 'I'}, {'L', 'I'}, {'L', 'I'}, {'Y', 'I'}, {'Y', 'I'}, {'Y', 'Y'}, {'Y', 'N'}, {'N', 'N'}, {'N', 'Y'}, {'N', 'Y'}, {'Y', 'Y'}, {'P', 'Y'}, {'P', 'P'}, {'P', 'P'}};

const int maxn = 100; 
char ans[maxn][maxn];

void print(ll N, ll M, bool sw) {
    cout << "yes\n";
    if (sw) {
        swap(N,M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) cout << ans[j][i];
            cout << '\n';
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) cout << ans[i][j];
        cout << '\n';
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M; cin >> N >> M;
    if (N%5 && M%5) {
        cout << "no\n";
        return 0;
    }

    bool sw = false;
    if (N%5) {
        sw = true;
        swap(N,M);
    }

    if (M == 1) {
        if (N > 5) {
            cout << "no\n";
            return 0;
        }
        cout << "yes\n";
        if (sw) swap(N,M);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) cout << 'I';
            cout << '\n';
        }
        return 0;
    }

    if (M == 2) {
        if (N == 5) {
            cout << "no\n";
            return 0;
        }
        int j = 0;
        int mm = N;
        while (mm >= 20) {
            mm-=10;
            for (int i = 0; i < 10; i++, j++) {
                for (int k = 0; k < 2; k++) {
                    ans[j][k] = diez[i][k];
                }
            }
        }

        if (mm == 10) {
            for (int i = 0; i < 10; i++, j++) {
                for (int k = 0; k < 2; k++) {
                    ans[j][k] = diez[i][k];
                }
            }
        }else {
            for (int i = 0; i < 15; i++, j++) {
                for (int k = 0; k < 2; k++) {
                    ans[j][k] = quince[i][k];
                }
            }
        }

        print(N, M, sw);
        return 0;
    }

    for (int i = 0; i < N; i+=5) {
        int j = 0;
        while (M-j > 5) {
            if ((i + j) % 2) {
                for (int aa = 0, bb = i; aa < 5; aa++, bb++) {
                    for (int xx = 0, yy = j; xx < 3; xx++,yy++) {
                        ans[bb][yy] = a3[aa][xx];
                    }
                }
            }else {
                for (int aa = 0, bb = i; aa < 5; aa++, bb++) {
                    for (int xx = 0, yy = j; xx < 3; xx++,yy++) {
                        ans[bb][yy] = b3[aa][xx];
                    }
                }
            }
            j += 3;
        }

        if (M-j == 3) {
            if ((i + j) % 2) {
                for (int aa = 0, bb = i; aa < 5; aa++, bb++) {
                    for (int xx = 0, yy = j; xx < 3; xx++,yy++) {
                        ans[bb][yy] = a3[aa][xx];
                    }
                }
            }else {
                for (int aa = 0, bb = i; aa < 5; aa++, bb++) {
                    for (int xx = 0, yy = j; xx < 3; xx++,yy++) {
                        ans[bb][yy] = b3[aa][xx];
                    }
                }
            }
            continue;
        }

        if (M-j == 4) {
            for (int aa = 0, bb = i; aa < 5; aa++, bb++) {
                for (int xx = 0, yy = j; xx < 4; xx++,yy++) {
                    ans[bb][yy] = four[aa][xx];
                }
            }
            continue;
        }

        for (int aa = 0, bb = i; aa < 5; aa++, bb++) {
            for (int xx = 0, yy = j; xx < 5; xx++,yy++) {
                ans[bb][yy] = cinco[aa][xx];
            }
        }
    }
    print(N,M,sw);
}

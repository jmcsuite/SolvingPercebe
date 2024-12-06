#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxb = 10;
const int maxn = 1<<maxb;

ll dp[maxn];
ll curr[maxn];

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M; cin >> N >> M;
    vector<vll> vadj;
    vadj.resize(N);
    for (int i = 0; i < N; i++) {
        vadj[i].resize(M);
        for (int j = 0; j < M; j++) {
            cin >> vadj[i][j];
        }
    }

    // leer vadj
    for (int j = M-1; j >= 0; j--) {
        for (int i = N-1; i >= 0; i--) {

            if ((i+j)%2 == 1) continue;

            for (int b = 0; b < maxn; b++) {
                curr[b] = 0;

                if (i < N-1 && i > 0) {
                    ll nexb = (b|(1<<i)) - (1<<i);
                    nexb = (nexb | (1<<(i-1)) | (1<<(i+1)));
                    ll cost = vadj[i-1][j] + vadj[i+1][j]; 
                    if (b&(1<<(i-1))) cost -= vadj[i-1][j];
                    if (b&(1<<(i+1))) cost -= vadj[i+1][j];
                    curr[b] = max(curr[b], dp[nexb] + vadj[i][j] - cost);
                }

                if (j < M-1 && j > 0) {
                    ll nexb = (b | (1<<i));
                    ll cost = vadj[i][j+1] + vadj[i][j-1];
                    if (b&(1<<i)) cost -= vadj[i][j-1];
                    curr[b] = max(curr[b], dp[nexb] + vadj[i][j] - cost);
                }
                ll nexb = (b|(1<<i)) - (1<<i);
                curr[b] = max(curr[b], dp[nexb]);
            }
            swap(curr, dp);
        }
    }
    cout << dp[0] << '\n';
}

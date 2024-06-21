#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 50;
const int maxr = maxn*maxn + 1;
const int mod = 1e9+7;

ll dp[maxr];
ll sum[maxr];


ll cant[maxr];


int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll D, R; cin >> D >> R;
    R*=R;

    for (int i = 0; i < maxr; i++) cant[i] = 1;

    for (int k = 0; k < D; k++) {
        for (int i = 0; i < maxr; i++) {
            sum[i] = dp[i];
            for (int j = 1; j*j + i <= R; j++) {
                sum[i] = (sum[i] + 2*dp[j*j + i] + 2*cant[j*j+i]*j) % mod;
            }
        }
        swap(dp, sum);

        for (int i = 0; i < maxr; i++){
            sum[i] = cant[i];
            for (int j = 1; j*j + i <= R; j++) {
                sum[i] = (sum[i] + 2*cant[i + j*j])%mod;
            }
        }
        swap(cant,sum);

        for (int i = 0; i < maxr; i++) sum[i] = 0;
    }
    dp[0] = ((dp[0]%mod) + mod) %mod;
    cout << dp[0] << '\n';
}

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 2e3;

ll dp[maxn][maxn];
ll vl[maxn];


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    for (int i=0; i<N; i++) cin>>vl[i];
    for (int i=1; i<N; i++) vl[i]+=vl[i-1];

    for (int i=N-1; i>=0; i--) {
        ll suffix = vl[N-1]; 
        if (i>0) suffix-=vl[i-1];
        for (int s=1; s<N; s++) {
            if (i + s*2 >= N) {
                dp[i][s] = suffix;
                continue;
            }
            dp[i][s] = max(dp[i][s-1], suffix - dp[i+s*2-1][s*2-1]);
            dp[i][s] = max(dp[i][s], suffix - dp[i+s*2][s*2]);
        }
    }
    cout << dp[0][1] << '\n';
}

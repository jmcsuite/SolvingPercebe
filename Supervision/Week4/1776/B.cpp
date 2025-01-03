#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 400;

double dp[maxn][maxn];

void build() {
    for (int d=1; d < maxn; d++) {
        for (int i=0; i+d<maxn; i++) {
            for (ll k=i; k<=i+d; k++) {
                double v1 = (k > i ? dp[i][k-1] : 0);
                double v2 = (k < i+d? dp[k+1][i+d] : 0);
                dp[i][i+d] += max(v1,v2)/(double(d)+1.0);
            }
            dp[i][i+d]+=10.0;
        }
    }
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie();
    build();
    ll N; cin>>N;
    cout << fixed << setprecision(7);
    cout << dp[1][N-2] + 10.0 << '\n';
}

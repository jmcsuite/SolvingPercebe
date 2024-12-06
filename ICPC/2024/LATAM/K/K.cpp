#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 1e6;
const int inf = 1e6*4;
ll dp[maxn+1][3];

bool isLetter(char x) {
    if (x == 'A') return true;
    if (x == 'E') return true;
    if (x == 'I') return true;
    if (x == 'O') return true;
    if (x == 'U') return true;
    if (x == 'Y') return true;
    return false;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    vector<string> vs(N);
    for (string& s: vs) cin >> s;
    for (int i=0; i<N; i++) dp[i][0] = dp[i][1] = dp[i][2] = inf;

    for (int i=N-1; i>=0; i--) {
        for (int j=0; j<3; j++) {
            for (int k=0; k<3; k++) {
                if (isLetter(vs[i][k])) {
                    dp[i][j] = min(dp[i][j], k+1+dp[i+1][0]);
                    break;
                }
                if(j+k >= 2) break;
                dp[i][j] = min(dp[i][j], k+1+dp[i+1][j+k+1]);
            }
        }
    }

    if (dp[0][0] == inf) {
        cout << "*\n";
    }
    else {
        cout << dp[0][0] << '\n';
    }
}

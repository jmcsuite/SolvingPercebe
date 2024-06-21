#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int maxn = 7490;
const int maxm = 5;

ll dp[maxn];
ll coins[maxm] = {50, 25, 10, 5, 1};

int main () {
    ios::sync_with_stdio(0);
    cin.tie(0);

    dp[0] = 1;
    for (int c = 0; c < maxm; c++) {
        for (int i = 0; i + coins[c] < maxn; i++) {
            if (dp[i] == 0) continue;
            dp[i+coins[c]] += dp[i];
        }
    }

    ll N;
    while (cin>>N) {
        cout << dp[N] << '\n';
    }
}

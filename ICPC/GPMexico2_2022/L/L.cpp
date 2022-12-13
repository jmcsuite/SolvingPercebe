#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const long long mod = 1e9+7;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N;
    cin >> N;
    if(N < 4){
        cout << 1 << endl;
        return 0;
    }

    vll dp(N+1);
    dp[1] = 1;
    for(int i = 2; i<=N; i++){
        ll cant = i/2;
        ll ans = (dp[i-1]-dp[i-1-cant])%mod;
        dp[i] = ans + dp[i-1];
    }

    ll ans =  ((dp[N] - dp[N-1])%mod + mod)%mod;
    cout << ans << '\n';
}
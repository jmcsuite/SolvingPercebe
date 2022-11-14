#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
ll maxVal = 1e4*5 + 10;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll Q, N; 
    cin >> Q >> N;
    vll vl(N);
    for(int i=0; i < N; i++) cin >> vl[i];
    ll maxV = maxVal + 300;
    vll dp(maxV);
    vll ans(maxV);
    dp[0] = 1;
    for(int i=0; i < maxVal; i++){
        if(dp[i] == 0) continue;
        for(int j=0; j < N; j++){
            dp[i + vl[j]]=1;
        }
    }

    for(int i=maxV-1; i >= 0; i--){
        ans[i] = ans[i+1];
        if(dp[i] == 1) ans[i] = i;
    }
    while(Q--){
        ll a;
        cin>>a;
        cout<<ans[a]-a<<'\n';
    }
}
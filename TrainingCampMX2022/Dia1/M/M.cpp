#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>; 
using pll = pair<ll,ll>;
using vpll = vector<pll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, V;
    cin>>N>>V;
    vll t(N);
    vll a(N);
    vpll dp;
    for(int i=0; i<N; i++) cin>>t[i];
    for(int i=0; i<N; i++) cin>>a[i];
    for(int i=0; i<N; i++){
        ll x = V*t[i]+a[i];
        ll y = V*t[i]-a[i];
        if(x < 0 || y < 0) continue;
        dp.push_back({x,y});
    }
    sort(dp.begin(),dp.end());
    vll lis;
    N = dp.size();
    for(int i=0; i<N; i++){
       auto it = upper_bound(lis.begin(),lis.end(),dp[i].second);
       size_t nex = it-lis.begin();
       if(it == lis.end()) lis.push_back(dp[i].second);
       lis[nex] = dp[i].second;
    }
    cout << lis.size() << '\n';
}
        


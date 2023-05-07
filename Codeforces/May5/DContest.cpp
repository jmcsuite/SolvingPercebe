#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N; 
        vll vl(N);
        vll dp1(N);
        vll dp2(N);

        for(int i=0; i<N; i++){
            cin>>vl[i];
        }
        dp1[N-1] = -1000000000000LL;
        ll maxi = dp1[N-1];
        for(int i=N-1; i>=0; i--){
            maxi--;
            dp1[i]=maxi;
            maxi=max(maxi,vl[i]);
        }

        dp2[N-1] = dp1[N-1];
        dp2[N-2] = dp2[N-1];

        maxi=dp1[N-1];
        for(int i=N-2; i>=0; i--){
            maxi--;
            dp2[i]=maxi;
            maxi=max(maxi,dp1[i]+vl[i]);
        }

        ll ans=dp1[N-1];
        for(int i=0; i<N; i++) ans=max(ans,vl[i]+dp2[i]);
        cout << ans << '\n';
    }
}

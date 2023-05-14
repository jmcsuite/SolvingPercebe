#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N,K; cin>>N>>K;
        vll vl(N);
        for(int i=0; i<N; i++) cin>>vl[i];
        sort(vl.begin(),vl.end());
        ll ans=0;
        for(int i=1; i<N; i++) vl[i]+=vl[i-1];
        ans = vl[N-1-K];
        for(int i=2,j=N-K; j<N && i<=N; i+=2,j++){
            ans = max(ans, (vl[j]-vl[i-1]));
        }
        cout << ans << '\n';
    }
}

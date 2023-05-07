#include<bits/stdc++.h>
using namespace std;
using ll=long long;
using vll=vector<ll>;

int main(){
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N;
        vll vl(N);
        vll v2(N);
        for(int i=0; i<N; i++) cin>>vl[i];
        for(int i=0; i<N; i++) v2[i]=vl[i]-vl[N-i-1];
        for(int i=0; i<N; i++) v2[i]=max(v2[i]*-1,v2[i]);

        ll maxi=0;
        for(int i=0; i<N; i++) maxi=max(v2[i],maxi);
        if(maxi == 0){
            cout << 0 << '\n';
            continue;
        }
        ll ans=v2[0];
        for(int i=1; i<N; i++) ans=gcd(v2[i],ans);
        cout << ans << '\n';
    }
}

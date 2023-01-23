#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
ll MOD = 1e9+7;
ll MOD2 = 999999191;

ll bin_exp(ll a,ll x, ll mod){
    ll ans = 1;
    while(x){
        if(x%2) ans = (ans*a)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N,M; cin>>N>>M;
        ll a1 = 0; ll a2 = 0;
        vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];
        sort(vl.rbegin(),vl.rend());
        for(int i=0; i<N; i++){
            if(a1 == a2 && a1 == 0){
                a1=bin_exp(M,vl[i],MOD2);
                a2=bin_exp(M,vl[i],MOD);
            }else{
                a1=(a1-bin_exp(M,vl[i],MOD2))%MOD2;
                a2=(a2-bin_exp(M,vl[i],MOD))%MOD;
            }
        }
        a2 = ((a2%MOD)+MOD)%MOD;
        cout << a2 << endl;
    }
}
        


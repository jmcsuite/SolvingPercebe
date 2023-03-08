#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int mod = 1e9+7;
const int maxn = 15;
int prime[maxn];
int ppow[maxn];

ll bin_exp(ll a, ll x){
    ll ans = 1;
    while(x){
        if(x%2) ans = (a*ans)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

ll hn(ll i){
    ll ans = bin_exp(prime[i],ppow[i])*(ppow[i])%mod;
    ll a2 = bin_exp(prime[i],ppow[i]+1)-1;
    a2%=mod;
    a2+=mod;
    a2%=mod;
    a2 = (a2*bin_exp(prime[i]-1,mod-2))%mod;
    ans = (ans+a2)%mod;
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    ll Q = 0;
    while(T--){
        ll N; cin>>N;
        ll fn = 1;
        ll h = 1;
        for(int i=0; i<N; i++) cin>>prime[i]>>ppow[i];
        for(int i=0; i<N; i++){
            h = (h * hn(i))%mod;
            // cout << prime[i] << ' ' << ppow[i] << ' ' << hn(i) << endl;
            fn = (fn*bin_exp(prime[i],ppow[i]))%mod;
        }
        ll ans = (h+fn)%mod;
        ans+=mod;
        ans%=mod;
        cout << "Case " << ++Q << ": ";
        cout << ans << '\n';
    }
}


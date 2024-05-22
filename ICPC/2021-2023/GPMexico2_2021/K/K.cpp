#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e6+2;
ll mod = 1e9+7;
ll bin_exp(ll a, ll x){
    ll ans = 1;
    while(x){
        if(x%2) ans = (ans*a)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

ll precalc[maxn];
void build(){
    precalc[1] = 0;
    for(int i=1; i<maxn;i++){
        ll num=bin_exp(2,i);
        num-=precalc[i];
        num = (num%mod + mod)%mod;
        for(int j=2; j*i<maxn; j++) precalc[j*i] = (precalc[j*i]+num)%mod;
    }
}

int main(){
    build();
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N; cout << precalc[N] << '\n';
    }
}



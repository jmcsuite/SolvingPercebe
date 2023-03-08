#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e5+2;
ll mod = 998244353;
ll fact[maxn];
ll prob[maxn];

ll bin_exp(ll a, ll x){
    ll ans = 1;
    while(x){
        if(x%2) ans = (ans*a)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

ll kdn(ll k, ll n){
    ll arriba = fact[n];
    ll abajo = (fact[k]*fact[n-k])%mod;
    arriba = (arriba*bin_exp(abajo,mod-2))%mod;
    return arriba;
}

void constFact(){
    fact[0] = 1;
    for(int i=1; i<maxn;i++) fact[i] = (fact[i-1]*i)%mod;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,K; cin>>N>>K;
    constFact();
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];
    for(int i=0; i<=K;i++){
        ll arriba = 1;
        ll abajo = N;
        arriba= (arriba*bin_exp(abajo,mod-2))%mod;
        arriba = bin_exp(arriba,i);
        ll a2 = N-1;
        ll b2 = N;
        a2 = (a2*bin_exp(b2,mod-2))%mod;
        a2 = bin_exp(a2,K-i);
        a2 = (a2*arriba)%mod;
        a2 = (a2*kdn(i,K))%mod;
        prob[i] = a2;
    }

    for(int i=1; i<maxn;i++) prob[i]= (prob[i]+prob[i-1])%mod;

    auto sumAcum = [&](ll i, ll j){
        j = min(j,K+1);
        if(i < 0) i = 0;
        if(j<=i) return ll(0);
        return (i==0 ? prob[j-1] : ll(prob[j-1]-prob[i-1]));
    };

    vll ans(10);
    auto solve = [&](ll x, ll i){
        ll exp = 1;
        while(i*exp-x<=K){
            ans[i] = (ans[i] + sumAcum(i*exp-x,(i+1)*exp-x))%mod;
            exp *= 10;
        }
    };

    for(int i=0; i<N; i++){
        for(int j=1; j<=9; j++){
            solve(vl[i],j);
        }
    }

    for(int i=1; i<=9; i++) cout << (ans[i]%mod+mod)%mod << '\n';
}


            


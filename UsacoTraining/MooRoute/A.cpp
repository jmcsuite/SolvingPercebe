#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll= vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=100000;
const int maxv=1000000;

ll fact[maxv+1];

const long long mod= 1000000007;

ll bin_lifting(ll a, ll x){
    ll ans = 1;
    while(x > 0){
        if( x%2 )  ans = (ans*a)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

ll n_k(ll n, ll k){
    ll ans = fact[n];
    ll div = (fact[k]*fact[n-k])%mod;
    div = bin_lifting(div, mod-2);
    ans = (ans * div)%mod;
    return ans;
}

ll vl[maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    fact[0] = 1;
    for(int i=1; i<=maxv; i++){
        fact[i] = (i * fact[i-1])%mod;
    }

    ll N; cin>>N;
    for(int i=0; i<N; i++) cin>>vl[i];
    for(int i=0; i<N; i++) vl[i]/=2;
    ll ans = 1;
    for(int i=1; i<N; i++){
        if(vl[i] > vl[i-1]){
            ans = (ans * n_k(vl[i]-1, vl[i-1]-1))%mod;
            //cout << vl[i] << ' ' << vl[i-1] << endl;
        }
        else{
            ans = (ans * n_k(vl[i-1],vl[i]))%mod;
        }
    }
    cout << ans << '\n';
}

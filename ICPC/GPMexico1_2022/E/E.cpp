#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
ll mod = 1e9+7;

ll mat_exp(ll a, ll x) {
    ll b = 1; 
    for(;x;x/=2,a=(a*a)%mod) if(x&1) b=(a*b)%mod;
    return b;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M, K; cin>>N>>M>>K;

    vector<vll> pir(M+1);
    for(int i = 0; i <= M; i++){
        pir[i].resize(i+1);
        pir[i][0] = 1;
        pir[i][i] = 1;
        for(int j = 1; j < i; j++){
            pir[i][j] = (pir[i-1][j-1] + pir[i-1][j])%mod;
        }
    }


 
    //return 0;
    vll func(K+1);
    func[0] = 0;
    func[1] = 1;
    for(ll i = 2; i <= K; i++){
        ll prev = mat_exp(i, N);
       
        for(ll j = 1; j < i; j++){
            ll mid = (func[i-j]*pir[i][j])%mod;
            prev = (prev-mid)%mod;
        }
        func[i] = prev;
    }
    
    ll ans = (pir[M][K]*func[K])%mod + mod;
    ans%=mod;
    cout << ans << '\n';
}

      

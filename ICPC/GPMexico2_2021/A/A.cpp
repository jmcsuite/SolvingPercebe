#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

ll mod = 998244353;
const int maxn = 14;
ll N,M;

pll edges[maxn*maxn];
ll dp[1<<maxn][maxn+1];
ll two_pow[maxn*maxn+1];

void init(){
    two_pow[0]=1;
    for(int i=1; i<=maxn*maxn; i++){
        two_pow[i] = (two_pow[i-1]*2)%mod;
    }
    for(int i=0; i<(1<<maxn);i++){
        for(int j=0; j<=maxn; j++){
            dp[i][j] = -1;
        }
    }
}


ll cedges(ll mask){
    ll ans=0;
    for(int i=0; i<M; i++){
        if(((1<<edges[i].first)& mask) == 0) continue;
        if(((1<<edges[i].second)& mask) == 0) continue;
        ans++;
    }
    return ans;
}

ll f_dp(ll mask,ll comp){
    if(mask == 0 && comp == 0) return 1;
    if(mask == 0) return 0;
    if(comp == 0) return 0;
    ll& d = dp[mask][comp];
    if(d != -1) return d;
    if(comp == 1){
        ll prev = cedges(mask);
        prev = two_pow[prev];
        for(int i=2; i<=N; i++){
            prev = ((prev-f_dp(mask,i))+mod)%mod;
        }
        prev%=mod;
        prev+=mod;
        prev%=mod;
        d = prev;
        return prev;
    }
    ll sub = mask;
    ll ans = 0;
    ll lsb = (mask & (-mask));
    while(1){
        ll xorSub = mask^sub;
        if(sub == 0 || xorSub == 0) {}
        else if((sub&lsb) != 0){
            ans = (ans + (f_dp(sub,1)*f_dp(xorSub,comp-1))%mod)%mod;
        }
        if(sub == 0) break;
        sub = (sub-1)&mask;
    }
    ans%=mod;
    ans+=mod;
    ans%=mod;
    d = ans;
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M;
    init();
    for(int i=0; i<M; i++) cin>>edges[i].first>>edges[i].second;
    for(int i=0; i<M; i++){
        edges[i].first--;
        edges[i].second--;
    }
    for(int i=1; i<=N; i++){
        cout << f_dp(two_pow[N]-1,i) << endl;
    }

    /*for(int i=0; i<(1<<N); i++){
        cout << i << endl;
        ll ii = i;
        while(i){
            cout << i%2;
            i/=2;
        }
        cout << endl;
        cout << f_dp(ii,1) << endl;
        cout << endl;
        i = ii;
    }*/
}



    
    
        
    

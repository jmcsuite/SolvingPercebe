#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int mod = 998244353;
const int maxn = 1e5;
vector<int> vadj[maxn];

ll N;

ll ansAbajo[maxn];
ll ansArriba[maxn];

ll bin_exp(ll a, ll x){
    ll ans = 1;
    while(x){
        if(x%2) ans = (ans*a) %mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}

ll calcMinAbajo(ll x){
    if(vadj[x].size() == 0){
        ansAbajo[x] = 1;
        return 1;
    }
    ll ans = maxn;
    for(size_t i=0; i<vadj[x].size(); i++){
        ans = min(calcMinAbajo(vadj[x][i]), ans);
    }
    ans++;
    ansAbajo[x] = ans;
    return ansAbajo[x]; 
}

void DFS(ll x, ll mini){
    mini = min(mini+1,ansAbajo[x]);
    ansArriba[x] = mini;
    for(size_t i = 0; i<vadj[x].size(); i++){
        DFS(vadj[x][i], mini);
    }
    return;
}

ll solve(){
    ll ans = 0;
    calcMinAbajo(0);
    DFS(0, maxn);
    for(int i=0; i<N; i++){
        ans = (ans+ansArriba[i])%mod;
        // cout << i << ' ' << ansArriba[i] << ' ' << ansAbajo[i] << endl;
    }
    ans = (ans*(bin_exp(N, mod-2)))%mod;
    ans+=mod;
    ans%=mod;
    return ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N;
    for(int i=1; i<N; i++){
        ll a; cin>>a; a--;
        vadj[a].push_back(i);
    }
    cout << solve() << endl;
}

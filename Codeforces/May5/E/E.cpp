#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=5000;
const int maxm=500;
bitset<maxn> les[maxn];
bitset<maxn> tmp;
pll w[maxm][maxn];
ll vl[maxn];
ll dp[maxn];

bool func(pll a, pll b){
    if(a.first != b.first) return a < b;
    return a > b;
}

ll N,M;
void apply(){
    for(int i=0; i<M; i++){
        tmp.reset();
        for(int j=0; j<N; j++){
            les[w[i][j].second] |= tmp;
            tmp[w[i][j].second]=1;
        }
    }
}
        
    


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>M>>N;
    for(int i=0; i<N; i++) cin>>vl[i];
    
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            cin>>w[i][j].first;
            w[i][j].second=j;
        }
        sort(w[i],w[i]+N);
    }

    apply();
    for(int i=0; i<M; i++) sort(w[i],w[i]+N,func);
    apply();
    sort(w[0], w[0]+N);
    for(int idx=N-1; idx>=0; idx--){
        int i=w[0][idx].second;
        dp[i]=vl[i];
        for(int dos=idx+1; dos<N; dos++){
            int j=w[0][dos].second;
            if(les[i][j]) continue;
            dp[i] = max(dp[i],dp[j]+vl[i]);
        }
    }

    ll ans=0;
    for(int i=0; i<N; i++) ans = max(ans,dp[i]);
    cout << ans << '\n';
}


    


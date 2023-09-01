#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 3e5;
const int maxDepth = 20;

ll dp[maxn][maxDepth];

void build(vll& vl){
    ll N = vl.size();
    for(int i=0; i<N; i++) dp[i][0] = vl[i];
    for(int k=1; k<maxDepth; k++){
        for(int i=0; i<N; i++){
            if(i+(1<<(k-1)) >= N) continue;
            dp[i][k] = min(dp[i][k-1],dp[i+(1<<(k-1))][k-1]);
        }
    }
}

// a inclusive, b exclusive
ll query(ll a, ll b){
    ll tam = b-a;
    ll k = 63-__builtin_clzll(tam);
    ll ans = dp[a][k];
    ans = min(ans, dp[b-(1<<k)][k]);
    return ans;
}
    



int main(){
    ll N,Q; cin>>N>>Q;
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];
    build(vl);

    while(Q--){
        ll a,b; cin>>a>>b; a--;
        cout << query(a,b) << endl;
    }
}




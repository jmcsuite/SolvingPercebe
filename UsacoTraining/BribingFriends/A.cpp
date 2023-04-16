#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

using item = pair<ll,pll>;

const int maxn=2000;
ll dp[maxn+1][maxn+1];
ll DPC[maxn+1][maxn+1];
ll P[maxn];
ll M[maxn];
ll C[maxn];


int main(){
    ios::sync_with_stdio(0);
    ll N,A,B; cin>>N>>A>>B;
    vector<item> vi(N);
    for(int i=0; i<N; i++) cin>>vi[i].second.first >> vi[i].second.second >> vi[i].first;
    sort(vi.begin(), vi.end());
    for(int i=0; i<N; i++){
        P[i] = vi[i].second.first;
        C[i] = vi[i].first;
        M[i] = vi[i].second.second;
    }

    for(int i=N-1; i>=0; i--){
        for(int j=0; j<=maxn; j++){
            dp[i][j] = dp[i+1][j];
            if(j-M[i] >= 0) dp[i][j] = max(dp[i][j], P[i]+dp[i+1][j-M[i]]);
        }
    }

    for(int i=0; i<N; i++) DPC[i][0] = dp[i][A];
    for(int i=N-1; i>=0; i--){
        for(int j=0; j<=maxn; j++){
            DPC[i][j] = DPC[i+1][j];
            if(C[i]*M[i] <= j){
                DPC[i][j] = max(DPC[i][j], DPC[i+1][j-C[i]*M[i]] + P[i]);
            }else{
                ll mooney = A-M[i]+(j/C[i]);
                if(mooney >= 0) DPC[i][j] = max(DPC[i][j], dp[i+1][mooney] + P[i]);
            }
        }
    }

    cout << DPC[0][B] << '\n';
}

    

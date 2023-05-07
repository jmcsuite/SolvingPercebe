#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=100001;
const int maxm=4;

ll dp[maxn][maxm];
ll vl[maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N;
        for(int i=0; i<N; i++) cin>>vl[i];
        for(int i=0; i<=N; i++){
            for(int j=0; j<3; j++) dp[i][j]=-1000000000LL;
        }

        for(int j=2; j>=0; j--){
            for(int i=N-1; i>=0; i--){
                dp[i][j] = max(vl[i]+dp[i+1][j+1], dp[i+1][j]);
                dp[i][j]--;
            }
        }

        ll ans=dp[N][3];
        for(int i=0; i<N; i++) ans=max(dp[i][0],ans);
        cout << ans+1 << '\n';
    }
}

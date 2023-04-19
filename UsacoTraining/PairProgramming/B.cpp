#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn=2002;

const long long mod = 1000000007;

ll dp[maxn][maxn][2];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N;
        string b,a;
        for(int i=0; i<N; i++){
            char c; cin>>c;
            if(c == '1') continue;
            if(c == '0') b.clear();
            if(c != '+') c = '0';
            b.push_back(c);
        }

        a = b;
        b.clear();
        
        for(int i=0; i<N; i++){
            char c; cin>>c;
            if(c == '1') continue;
            if(c == '0') b.clear();
            if(c != '+') c = '0';
            b.push_back(c);
        }

        ll M = b.size(); N = a.size();
        for(int i=0; i<=N; i++) for(int j=0; j<=M; j++) dp[i][j][0] = dp[i][j][1] = 0;
        for(int i=0; i<N; i++) dp[i][M][0] = 1;
        for(int i=0; i<M; i++) dp[N][i][1] = 1;
        dp[N][M][0] = 1;


        for(int i=N-1; i>=0; i--){
            for(int j=M-1; j>=0; j--){
                for(int k=0; k<2; k++){
                    if(k == 0){
                        dp[i][j][k] = (dp[i+1][j][1] + dp[i+1][j][0]) % mod;
                    }else{
                        dp[i][j][k] = dp[i][j+1][1];
                        if(a[i] != b[j]) dp[i][j][k] = (dp[i][j][k] + dp[i][j+1][0])%mod;
                    }
                }
            }
        }

        /*for(int i=0; i<=N; i++){
            for(int j=0; j<=M; j++){
                cout << dp[i][j][0] << ' ';
            }
            cout << endl;
        }
        cout << endl;
        for(int i=0; i<=N; i++){
            for(int j=0; j<=M; j++){
                cout << dp[i][j][1] << ' ';
            }
            cout << endl;
        }

        cout << a << ' ' << b << endl;*/

        ll ans = (dp[0][0][0] + dp[0][0][1])%mod;
        ans += mod;
        ans %= mod;
        cout << ans << '\n';
    }
}

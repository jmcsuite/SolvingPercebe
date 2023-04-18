#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const long long mod = 1000000007;
const int maxn=2002;

ll dp[maxn][maxn];
ll rowSum[maxn][maxn];
ll colSum[maxn][maxn];

ll nextN[maxn];
ll nextM[maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    while(T--){
        ll N; cin>>N;
        string a,b;
        for(int i=0; i<N; i++){
            char c; cin>>c;
            if(c == '0') a.clear();
            if(c == '1') continue;
            a.push_back(c);
        }
        for(int i=0; i<N; i++){
            char c; cin>>c;
            if(c == '0') b.clear();
            if(c == '1') continue;
            b.push_back(c);
        }

        N = a.size();
        ll M = b.size();
        for(int i=0; i<=N; i++){
            for(int j=0; j<=M; j++) dp[i][j] = rowSum[i][j] = colSum[i][j] = 0;
        }
        for(int i=0; i<N; i++) dp[i][M]=rowSum[i][M]=colSum[i][M]=1;
        for(int j=0; j<M; j++) dp[N][j]=rowSum[N][j]=colSum[N][j]=1;
        dp[N][M] = 1;
        rowSum[N][M] = colSum[N][M] = 1;
        for(int i=N-1; i>=0; i--) colSum[i][M] = (colSum[i][M] + colSum[i+1][M])%mod;
        for(int j=M-1; j>=0; j--) rowSum[N][j] = (rowSum[N][j] + rowSum[N][j+1])%mod;


        
        nextN[N]=N;
        for(int i=N-1; i>=0; i--) {
            nextN[i] = nextN[i+1];
            if(a[i] == '+') nextN[i] = i;
        }

        nextM[M]=M;
        for(int i=M-1; i>=0; i--) {
            nextM[i] = nextM[i+1];
            if(b[i] == '+') nextM[i] = i;
        }

        cout << a << ' ' << b << endl;
        for(int i=0; i<N; i++) cout << nextN[i] << ' ';
        cout << endl;
        for(int i=0; i<M; i++) cout << nextM[i] << ' ';
        cout << endl;



        for(int i=N-1; i>=0; i--){
            for(int j=M-1; j>=0; j--){
                ll ni = nextN[i];
                ll nj = nextM[j];
                if(ni == N && nj == M){
                    dp[i][j] = 1;
                }else{
                    if(ni != N){
                        dp[i][j] = (rowSum[ni+1][j]);
                        if(nj != M) dp[i][j] = (dp[i][j] - rowSum[ni+1][nj+1])%mod;
                    }
                    if(nj != M){
                        dp[i][j] = (dp[i][j] + colSum[i][nj+1]) %mod;
                        if(ni != N) dp[i][j] = (dp[i][j] - colSum[ni+1][nj+1])%mod;
                    }
                }
                rowSum[i][j] = (dp[i][j] + rowSum[i][j] + rowSum[i][j+1])%mod;
                colSum[i][j] = (dp[i][j] + colSum[i][j] + colSum[i+1][j])%mod;
            }
        }

        for(int i=0; i<=N; i++){
            for(int j=0; j<=M; j++) cout << dp[i][j] << ' ';
            cout << endl;
        }
        cout << endl;
        for(int i=0; i<=N; i++){
            for(int j=0; j<=M; j++) cout << rowSum[i][j] << ' ';
            cout << endl;
        }
        cout << endl;
        for(int i=0; i<=N; i++){
            for(int j=0; j<=M; j++) cout << colSum[i][j] << ' ';
            cout << endl;
        }

        dp[0][0] = ((dp[0][0]%mod) + mod)%mod;
        cout << dp[0][0] << endl;
    }
}


#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const long long mod = 1000000007;
const int maxn=2002;

ll dp[maxn][maxn][2];
ll rowSum[maxn][maxn][2];
ll colSum[maxn][maxn][2];

ll nextN[maxn];
ll nextM[maxn];

ll nextND[maxn];
ll nextMD[maxn];

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
        for(int i=0; i<=N+1; i++){
            for(int j=0; j<=M+1; j++) dp[i][j][0] = rowSum[i][j][0] = colSum[i][j][0] = dp[i][j][1] = rowSum[i][j][1] = colSum[i][j][1] = 0;
        }
        for(int i=0; i<N; i++) {
            if(a[i] == '+') dp[i][M][0]=rowSum[i][M][0]=colSum[i][M][0]=1;
            else dp[i][M][1]=rowSum[i][M][1]=colSum[i][M][1]=1;
        }
        for(int j=0; j<M; j++) {
            if(b[j] == '+') dp[N][j][0]=rowSum[N][j][0]=colSum[N][j][0]=1;
            else dp[N][j][1]=rowSum[N][j][1]=colSum[N][j][1]=1;
        }
        dp[N][M][0] = dp[N][M][1] = 1;
        rowSum[N][M][0] = colSum[N][M][0] = rowSum[N][M][1] = colSum[N][M][1] = 1;
        for(int i=N-1; i>=0; i--) rowSum[i][M][0] = (rowSum[i][M][0] + rowSum[i+1][M][0])%mod;
        for(int j=M-1; j>=0; j--) colSum[N][j][0] = (colSum[N][j][0] + colSum[N][j+1][0])%mod;
        for(int i=N-1; i>=0; i--) rowSum[i][M][1] = (rowSum[i][M][1] + rowSum[i+1][M][1])%mod;
        for(int j=M-1; j>=0; j--) colSum[N][j][1] = (colSum[N][j][1] + colSum[N][j+1][1])%mod;



        
        nextN[N]=N;
        for(int i=N-1; i>=0; i--) {
            nextN[i] = nextN[i+1];
            if(a[i] == '+') nextN[i] = i;
        }

        nextND[N]=N;
        for(int i=N-1; i>=0; i--) {
            nextND[i] = nextND[i+1];
            if(a[i] != '+') nextND[i] = i;
        }

        nextM[M]=M;
        for(int i=M-1; i>=0; i--) {
            nextM[i] = nextM[i+1];
            if(b[i] == '+') nextM[i] = i;
        }
        
        nextMD[M]=M;
        for(int i=M-1; i>=0; i--) {
            nextMD[i] = nextMD[i+1];
            if(b[i] != '+') nextMD[i] = i;
        }

        for(int i=N-1; i>=0; i--){
            for(int j=M-1; j>=0; j--){
                ll idx=0;
                if(a[i] == '+' || b[j] == '+'){
                    ll na = nextND[i];
                    ll nb = nextMD[j];
                    if(a[i] == '+'){
                        dp[i][j][idx] = (rowSum[i+1][nb][idx+1] - rowSum[na+1][nb][idx+1])%mod;
                        if(b[j] == '+') dp[i][j][idx] = (dp[i][j][idx] + dp[i][nb][idx+1])%mod;
                    }
                    if(b[j] == '+'){
                        dp[i][j][idx] = (dp[i][j][idx] + colSum[na][j+1][idx+1] - colSum[na][nb+1][idx+1])%mod;
                        if(a[i] == '+') dp[i][j][idx] = (dp[i][j][idx] + dp[na][j][idx+1])%mod;
                    }
                    if(a[i] == '+' && b[j] == '+') dp[i][j][idx] = (dp[i][j][idx] - dp[na][nb][idx+1])%mod;
                }
                rowSum[i][j][idx] = (dp[i][j][idx] + rowSum[i+1][j][idx])%mod; 
                colSum[i][j][idx] = (dp[i][j][idx] + colSum[i][j+1][idx])%mod;

                idx++;
                if(a[i] != '+' || b[j] != '+'){
                    ll na = nextN[i];
                    ll nb = nextM[j];
                    /*if(i == 1 && j == 0){
                        cout << "WTF :" << endl;
                        cout << na << ' ' << nb << endl;
                    }*/
                    if(a[i] != '+'){
                        dp[i][j][idx] = (rowSum[i+1][nb][idx-1] - rowSum[na+1][nb][idx-1])%mod;
                        if(b[j] != '+') dp[i][j][idx] = (dp[i][j][idx] + dp[i][nb][idx-1])%mod;
                    }
                    if(b[j] != '+'){
                        dp[i][j][idx] = (dp[i][j][idx] + colSum[na][j+1][idx-1] - colSum[na][nb+1][idx-1])%mod;
                        if(a[i] != '+') dp[i][j][idx] = (dp[i][j][idx] + dp[na][j][idx-1])%mod;
                    }
                    if(a[i] != '+' && b[j] != '+') dp[i][j][idx] = (dp[i][j][idx] - dp[na][nb][idx-1])%mod;
                }
                rowSum[i][j][idx] = (dp[i][j][idx] + rowSum[i+1][j][idx])%mod; 
                colSum[i][j][idx] = (dp[i][j][idx] + colSum[i][j+1][idx])%mod;
            }
        }

        /*
        for(int i=0; i<=N; i++){
            for(int j=0; j<=M; j++) cout << dp[i][j][0] << ' ';
            cout << endl;
        }
        cout << endl;
        for(int i=0; i<=N; i++){
            for(int j=0; j<=M; j++) cout << dp[i][j][1] << ' ';
            cout << endl;
        }
        cout << endl;
        for(int i=0; i<=N; i++){
            for(int j=0; j<=M; j++) cout << rowSum[i][j][0] << ' ';
            cout << endl;
        }
        cout << endl;
        for(int i=0; i<=N; i++){
            for(int j=0; j<=M; j++) cout << colSum[i][j][0] << ' ';
            cout << endl;
        }*/

        dp[0][0][0] = ((dp[0][0][0]%mod) + mod)%mod;
        dp[0][0][1] = ((dp[0][0][1]%mod) + mod)%mod;
        ll aa = (dp[0][0][0] + dp[0][0][1]) %mod;
        cout << aa << '\n';
    }
}


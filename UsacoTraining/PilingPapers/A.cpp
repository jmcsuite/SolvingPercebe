#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=300;
const long long mod= 1e9+7;
const int maxm=19;

ll dp[maxm][maxm][3];
ll AMatrix[maxn][maxn];
ll BMatrix[maxn][maxn];


void fill(string& A, string& S, ll matrix[maxn][maxn]){
    ll N = S.size();
    ll M = A.size();
    for(int i=0; i<N; i++){
        //clear dp;
        for(int j=0; j<=M; j++){
            for(int k=0; k<=M; k++){
                for(int z=0; z<3; z++){
                    if(k == 0 && z == 1){
                        dp[j][k][z] = 1;
                        continue;
                    }
                    dp[j][k][z] = 0;
                }
            }
        }

        for(int j=i; j<N; j++){
            // calcular esta DP
            for(int k=M-1;k>=0; k--){
               for(int h=0; h+k <= M; h++){
                  // derecha
                  if(h+k < M){
                      dp[h][k+1][0] = (dp[h][k+1][0] + dp[h][k][0]) % mod;
                      dp[h][k+1][2] = (dp[h][k+1][2] + dp[h][k][2]) % mod;
                      ll nf=2;
                      if(S[j] == A[h+k]) nf=1;
                      if(S[j] < A[h+k]) nf=0;
                      dp[h][k+1][nf] = (dp[h][k+1][nf]+dp[h][k][1]) % mod;
                  }
                  // izquierda
                  if(h > 0){
                      if(S[j] == A[h-1]){
                          dp[h-1][k+1][0] = (dp[h-1][k+1][0] + dp[h][k][0]) % mod;
                          dp[h-1][k+1][1] = (dp[h-1][k+1][1] + dp[h][k][1]) % mod;
                          dp[h-1][k+1][2] = (dp[h-1][k+1][2] + dp[h][k][2]) % mod;
                      }else if(S[j] < A[h-1]){
                          dp[h-1][k+1][0] = (dp[h-1][k+1][0] + dp[h][k][0] + dp[h][k][1] + dp[h][k][2])%mod;
                      }else{
                          dp[h-1][k+1][2] = (dp[h-1][k+1][2] + dp[h][k][0] + dp[h][k][1] + dp[h][k][2])%mod;
                      }
                  }
               }
            }
            matrix[i][j] = (dp[0][M][1] + dp[0][M][0])%mod;
            for(int k=0; k<M; k++) matrix[i][j] = (matrix[i][j] + dp[0][k][0] + dp[0][k][1] + dp[0][k][2])%mod;
        }
    }
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; ll dummy;
    string A,B;
    cin>>N>>dummy>>B;
    dummy--;
    A = to_string(dummy);
    string S;
    for(int i=0; i<N; i++){
        char c; cin>>c;
        S.push_back(c);
    }
    fill(A,S,AMatrix);
    fill(B,S,BMatrix);
    
    ll Q; cin>>Q;
    for(int i=0; i<Q; i++){
        ll a,b; cin>>a>>b; a--; b--;
        ll ans = ((BMatrix[a][b] - AMatrix[a][b]) % mod + mod)%mod;
        cout << ans << '\n';
    }

    /*cout << "AMATRIX" << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << AMatrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "END" << endl;
    cout << "B MATRIX" << endl;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cout << BMatrix[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "END" << endl;*/
}

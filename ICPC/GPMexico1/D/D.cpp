#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<(b);i++)
using namespace std;
using ll = long long;
using vll = vector<long long>;
using pii = pair<int,int>;

const int maxN = 101;
const int maxn = 101;
ll mod= 1e9+7;
int n;

struct mat {
    ll val[maxn][maxn];
    mat(){ memset(val, 0, sizeof(val)); }
    ll* operator[] (ll i) {return val[i];}
} ady;
void mat_mul(mat &a, mat &b) {
    mat c;
    rep(i,0,n) rep(j,0,n) rep(k,0,n)
        c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
    memcpy(&a,&c,sizeof a);
}
void mat_exp(mat &a, ll x) {
    mat b; rep(i,0,n) b[i][i]=1;
    for(;x;x/=2,mat_mul(a,a)) if(x&1) mat_mul(b,a);
    memcpy(&a,&b,sizeof a);
}


int main(){
    ll N, M, K;
    cin >> N >> M >> K;
    n = N+1;
    vector<pii> edges(M);
    ll a, b;
    for(int i = 0; i < M; i++){
        cin >> a >> b;
        ady[a][b] = 1;
        ady[b][a]= 1;
    }
    mat_exp(ady, K);
    ll ans = 0;
    for(int i = 0; i <= N; i++) ans = (ans + ady[1][i])%mod;
    cout << ans << '\n';
    
}

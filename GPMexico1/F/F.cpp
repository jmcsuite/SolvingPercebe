#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define rep(i,a,b) for(int i=(a);i<(b);i++)
const int maxn = 2;
int n = 2;
ll mod = 1e9 + 7;

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
    ios::sync_with_stdio(0);
    cin.tie(0);
    ady[0][0] = 0;
    ady[0][1] = 1;
    ady[1][0] = 1;
    ady[1][1] = 1;
    ll N, M;
    cin >> N >> M;
    ll ans = 1;
    int prev = 0;
    vector<int> input(M+1);
    vector<int> dp(1e6+1);
    dp[0] = 0;
    dp[1] = 1;
    for(int i = 2; i < 1e6+1; i++) dp[i] = (dp[i-1] + dp[i-2])%mod;

    for(int i = 0; i<M; i++) cin>>input[i];
    input[M] = N+1;
    sort(input.begin(), input.end());

    for(int i = 0; i<=M;i++){
        int B = input[i];
        int dif = B-prev;
        if(dif < 1e6+1) ans = (ans*dp[dif])%mod;
        else{
            ady[0][0] = 0;
            ady[0][1] = 1;
            ady[1][0] = 1;
            ady[1][1] = 1;
            mat_exp(ady, dif-2);
            ll seg = (ady[1][0] + ady[1][1])%mod;
            ans = (ans*seg)%mod;
        }
        prev = B+1;
    }

    cout << ans << '\n';
}
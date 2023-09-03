#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=1001;

ll forest[maxn][maxn];
ll dp[maxn][maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,Q; cin>>N>>Q;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            char a; cin>>a;
            if(a == '.') continue;
            dp[i][j]=1;
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(i>0) dp[i][j] += dp[i-1][j];
            if(j>0) dp[i][j] += dp[i][j-1];
            if(i>0 && j>0) dp[i][j] -= dp[i-1][j-1];
        }
    }

    // ( a, b]
    auto query = [&](ll xi, ll yi, ll xf, ll yf){
        ll ans = dp[xf][yf];
        if(xi >= 0) ans -= dp[xi][yf];
        if(yi >= 0) ans -= dp[xf][yi];
        if(xi >= 0 && yi >= 0) ans += dp[xi][yi];
        return ans;
    };

    while(Q--){
        ll xi, yi, xf, yf; cin>>xi>>yi>>xf>>yf;
        xi--; yi--; xf--; yf--;
        xi--; yi--;

        cout << query(xi, yi, xf, yf) << '\n';
    }
}

    


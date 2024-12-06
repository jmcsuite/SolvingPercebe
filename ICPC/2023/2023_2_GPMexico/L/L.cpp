#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using vll = vector<ll>;
const int maxn = 10*50 + 1;

ll dp[maxn][maxn];
ll tmp[maxn][maxn];


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N,A,B,C; cin>>N>>A>>B>>C;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];
    ll tot = 0;
    for(int i=0; i<N; i++) tot += vl[i];
    

    for(int i=0; i<maxn; i++){
        for(int j=0; j<maxn; j++){
            ll tc = tot - i - j;
            tc = max((ll)0,tc);

            ll ti = i/A;
            if(i%A) ti++;

            ll tj = j/B;
            if(j%B) tj++;

            ll tk = tc/C;
            if(tc%C) tk++;

            dp[i][j] = max(max(ti,tj), tk);
        }
    }

    for(int k=N-1; k>=0; k--){
        for(int i=0; i<maxn; i++){
            for(int j=0; j<maxn; j++){
                tmp[i][j] = dp[i][j];
                if(i+vl[k] < maxn) tmp[i][j] = min(tmp[i][j], dp[i+vl[k]][j]);
                if(j+vl[k] < maxn) tmp[i][j] = min(tmp[i][j], dp[i][j+vl[k]]);
            }
        }
        swap(dp, tmp);
    }

    cout << dp[0][0] << '\n';
}


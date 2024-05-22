#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=500;
ll vadj[maxn][maxn];

ll dp[maxn][maxn];

ll dx[8]={0,1,1,1,0,-1,-1,-1};
ll dy[8]={1,1,0,-1,-1,-1,0,1};

using item= pair<ll,pll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M;
    cin>>N>>M;
    for(int i=0; i<N; i++){
        for(int j=0;j<M; j++){
            cin>>vadj[i][j];
            vadj[i][j]*=-1;
        }
    }

    ll ans=0;
    ll a,b;
    cin>>a>>b; a--; b--;
    priority_queue<item> pq;
    pq.push({vadj[a][b],{a,b}});
    while(!pq.empty()){
        item pp = pq.top(); pq.pop();
        ll xVal = pp.first;
        ll x = pp.second.first;
        ll y = pp.second.second;
        if(dp[x][y] > xVal) continue;
        dp[x][y] = xVal;
        xVal = min(xVal,vadj[x][y]);
        //cout << x << ' ' << y << ' ' << pp.first << ' ' << vadj[x][y] << endl;
        if(xVal <= 0) continue;
        ans += xVal;
        for(int k=0; k<8; k++){
            ll nx = dx[k]+x;
            ll ny = dy[k]+y;
            if(nx < 0 || ny < 0) continue;
            if(nx >= N || ny >= M) continue;
            ll nVal = min(xVal, vadj[nx][ny]);
            if(dp[nx][ny] >= nVal) continue;
            pq.push({nVal,{nx,ny}});
            dp[nx][ny]=nVal;
        }
    }
    cout << ans << '\n';
}

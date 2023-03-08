#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

int dx[8] = {-1,-1,0,1,1,1,0,-1};
int dy[8] = {0,1,1,1,0,-1,-1,-1};
const int maxn=1e3+1;
int vadj[maxn][maxn];
int vis[maxn][maxn];

ll N,M;

bool check(ll i, ll j){
    if(i<0 || j < 0) return false;
    if(i >= N || j >= M) return false;
    return true;
}

ll DFS(ll i, ll j){
    if(vis[i][j]) return vis[i][j];
    ll ans = 0;
    for(int k=0; k<8; k++){
        ll di = i+dx[k];
        ll dj = j+dy[k];
        if(check(di,dj) && vadj[di][dj] == vadj[i][j]+1){
            ans = max(ans, DFS(di,dj));
        }
    }
    ans++;
    return vis[i][j] = ans;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            char c; cin>>c;
            int cc = c-'A';
            vadj[i][j] = cc;
        }
    }
    ll ans = 0; 
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            ans = max(ans, DFS(i,j));
        }
    }
    cout << ans << '\n';
}
    

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 1000;
const int maxm = 1000;

char inp[maxn][maxm];
ll dis[maxn][maxm];
ll nul = 1e9;
ll N,M;
bool check(ll i, ll j){
    if(i<0 || j<0) return false;
    if(i>=N || j>=M) return false;
    if(dis[i][j] != nul) return false;
    if(inp[i][j] == '#' || inp[i][j] == 'X') return false;
    return true;
}

int dx[4] = {0,1,0,-1};
int dy[4] = {-1,0,1,0};
char an[4] = {'L','D','R','U'};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M;
    ll ni=0; ll nj=0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin>>inp[i][j];
            if(inp[i][j] == 'E'){
                ni = i;
                nj = j;
            }
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            dis[i][j] = nul;
        }
    }

    queue<pair<pll,ll>> q;
    q.push({{ni,nj},0});
    dis[ni][nj] = 0;
    while(!q.empty()){
        auto node = q.front();
        q.pop();
        ll i,j; i=node.first.first;
        j = node.first.second;
        ll ti = node.second;
        for(int k=0; k<4; k++){
            ll ni=i+dx[k];
            ll nj=j+dy[k];
            if(!check(ni,nj)) continue;
            dis[ni][nj] = ti+1;
            q.push({{ni,nj},ti+1});
        }
    }

    ll T;
    cin>>T; 
    while(T--){
        ll a,b;cin>>a>>b;
        a--;b--;
        if(inp[a][b] == '#'){
            cout << "W\n";
            continue;
        }
        if(inp[a][b] == 'X'){
            cout << "X\n";
            continue;
        }
        if(inp[a][b] == 'E'){
            cout << "E\n";
            continue;
        }
        ll ans = nul;
        char charans = '?';
        for(int k=0; k<4; k++){
            ll di = a+dx[k];
            ll dj = b+dy[k];
            if(di<0 || dj<0) continue;
            if(di >= N || dj >= M) continue;
            if(dis[di][dj] < ans) {
                ans = dis[di][dj];
                charans = an[k];
            }
        }
        cout << charans << '\n';
    }
}









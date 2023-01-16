 #include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
ll N,ans,M;

int dx[4] = {1,0,-1,0};
int dy[4] = {0,1,0,-1};

bool check(ll i, ll j){
    if(i < 0 || j < 0) return false;
    if(i >= N || j >= M) return false;
    return true;
}

void BFS(ll i, ll j, vector<vll>& vis, vector<vll>& vadj){
    ans = 0;
    deque<pair<ll,pll>> q;
    q.push_front({0,{i,j}});
    while(!q.empty()){
        auto n = q.front();
        q.pop_front();
        ll t = n.first;
        i = n.second.first;
        j = n.second.second;
        if(vis[i][j]) continue;
        vis[i][j] = 1;
        if(vadj[i][j] == 0) ans+=t;
        if(vadj[i][j] == 0) t = 0;
        for(int k=0;k<4;k++){
            ll nt = t;
            ll ni = i + dx[k];
            ll nj = j + dy[k];
            if(!check(ni,nj)) continue;
            if(vadj[ni][nj]) nt++;
            if(vis[ni][nj]) continue;
            if(vadj[ni][nj]) q.push_back({nt,{ni,nj}});
            else q.push_front({nt,{ni,nj}});
        }
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M;
    N+=2; M+=2;
    vector<vector<char>> inp(N);
    for(int i=0; i<N; i++) inp[i].resize(M);
    for(int i=1; i<N-1; i++){
        for(int j=1; j<M-1; j++) cin>>inp[i][j];
    }
    vector<vll> vadj(N*2);
    for(int i=0; i<N*2; i++) vadj[i].resize(M*2);
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(inp[i][j] == '/'){
                vadj[i*2+1][j*2]=1;
                vadj[i*2][j*2+1]=1;
            }
            if(inp[i][j] == '\\'){
                vadj[i*2][j*2]=1;
                vadj[i*2+1][j*2+1]=1;
            }
        }
    }

    N=N*2;
    M=M*2;
    //for(int i=0; i<N;i++){
     //   for(int j=0; j<M; j++){
      //      cout << (vadj[i][j] == 1? '0' : '*');
       // }
       // cout << endl;
    // }
    vector<vll> vis(N);
    for(int i=0; i<N; i++) vis[i].resize(M);
    BFS(0,0,vis,vadj);
    cout << ans << '\n';
}




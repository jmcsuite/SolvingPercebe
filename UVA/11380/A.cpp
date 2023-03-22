#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=30*30*2+2;

namespace Dinics{
    map<ll,ll> vadj[maxn];
    vpll layered[maxn];
    vpll layeredSum[maxn];
    int level[maxn];
    int index[maxn];
    const long long maxFlow=1e16;

    void clear(int N){
        for(int i=0; i<N; i++) vadj[i].clear();
    }

    void buildLayered(int N, int S){
        for(int i=0; i<N; i++) level[i]=-1;
        queue<int> q;
        queue<int> q2;
        int step=1;
        level[S]=0;
        q.push(S);
        while(1){
            while(!q.empty()){
                int x=q.front();
                q.pop();
                for(pll yy:vadj[x]){
                    int y=yy.first;
                    if(level[y] != -1) continue;
                    if(yy.second <= 0) continue;
                    level[y]=step;
                    q2.push(y);
                }
            }
            if(q2.empty()) break;
            step++;
            while(!q2.empty()){
                q.push(q2.front());
                q2.pop();
            }
        }
        for(int i=0; i<N; i++){
            layered[i].clear();
            layeredSum[i].clear();
            for(pll yy:vadj[i]){
                if(level[i]+1 != level[yy.first]) continue;
                layered[i].push_back(yy);
                layeredSum[i].push_back(yy);
            }
        }
    }

    ll blockFlow(int x, ll flow, int T){
        if(flow == 0) return flow;
        if(x == T) return flow;
        if(index[x] >= (ll)layered[x].size()) return 0;
        for(size_t i=index[x]; i<layered[x].size(); index[x]++,i=index[x]){
            ll nextFlow = min(flow, layered[x][i].second);
            ll attempt = blockFlow(layered[x][i].first, nextFlow, T);
            if(attempt!=0){
                layered[x][i].second-=attempt;
                if(layered[x][i].second==0) index[x]++;
                return attempt;
            }
        }
        return 0;
    }

    ll blockPaths(ll N,ll S, ll T){
        for(int i=0; i<N; i++) index[i]=0;
        ll ans=0;
        while(1){
            ll flow = blockFlow(S,maxFlow, T);
            ans+=flow;
            if(flow==0) return ans;
        }
    }

    ll dinics(ll N, ll S, ll T){
        ll ans=0;
        while(1){
            buildLayered(N,S);
            ll push = blockPaths(N,S,T);
            ans+=push;
            if(push==0) return ans;
            for(int i=0; i<N; i++){
                for(size_t j=0; j<layered[i].size(); j++){
                    vadj[i][layered[i][j].first] = layered[i][j].second;
                    vadj[layered[i][j].first][i] += layeredSum[i][j].second-layered[i][j].second;
                }
            }
        }
    }
}

ll vadj[30][30];
ll indexIn(ll i, ll j, ll N, ll M){
    return i*M+j;
}
ll indexOut(ll i, ll j, ll N, ll M){
    return N*M+indexIn(i,j,N,M);
}
int dx[4]={0,1,0,-1};
int dy[4]={-1,0,1,0};
bool check(ll i, ll j, ll N, ll M){
    if(i < 0 || j<0) return false;
    if(i>=N || j>=M) return false;
    return true;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M,C;
    while(cin>>N>>M>>C){
        Dinics::clear(2*N*M+2);
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                char a; cin>>a;
                if(a == '~') vadj[i][j]=0;
                if(a == '*') vadj[i][j]=1;
                if(a == '.') vadj[i][j]=2;
                if(a == '@') vadj[i][j]=3;
                if(a == '#') vadj[i][j]=4;
            }
        }

        ll S = 2*N*M;
        ll T = 2*N*M+1;
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(vadj[i][j] == 0) continue;
                ll x=indexIn(i,j,N,M);
                ll y=indexOut(i,j,N,M);
                if(vadj[i][j] <= 2) {
                    Dinics::vadj[x][y]=1;
                }
                if(vadj[i][j] > 2){
                    Dinics::vadj[x][y]=Dinics::maxFlow;
                }
                if(vadj[i][j] == 1){
                    Dinics::vadj[S][x]=1;
                }
                if(vadj[i][j] == 4){
                    Dinics::vadj[y][T]=C;
                }
            }
        }

        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                for(int k=0; k<4; k++){
                    ll di=i+dx[k];
                    ll dj=j+dy[k];
                    if((!check(di,dj,N,M)) || (vadj[di][dj]==0)) continue;
                    ll x = indexOut(i,j,N,M);
                    ll y = indexIn(di,dj,N,M);
                    Dinics::vadj[x][y]=Dinics::maxFlow;
                }
            }
        }

        ll mf = Dinics::dinics(2*N*M+2, S, T);
        cout << mf << '\n';
    }
}


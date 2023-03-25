#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=202;

namespace Dinics{
    map<ll,ll> vadj[maxn];
    vpll layered[maxn];
    vpll layeredSum[maxn];
    int level[maxn];
    int index[maxn];
    const long long maxFlow = 1e16;

    void clear(int N){
        for(int i=0; i<N; i++) vadj[i].clear();
    }

    void buildLayered(int N, int S){
        for(int i=0; i<N; i++) level[i] = -1;
        queue<int> q;
        queue<int> q2;
        int step=1;
        level[S]=0;
        q.push(S);
        while(1){
            while(!q.empty()){
                int x=q.front();
                q.pop();
                for(pll yy: vadj[x]){
                    int y=yy.first;
                    if(level[y] != -1) continue;
                    if(yy.second <= 0) continue;
                    level[y] = step;
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

    ll blockPaths(ll N, ll S, ll T){
        for(int i=0; i<N; i++) index[i]=0;
        ll ans = 0;
        while(1){
            ll flow=blockFlow(S,maxFlow,T);
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
                    vadj[i][layered[i][j].first]=layered[i][j].second;
                    vadj[layered[i][j].first][i] += layeredSum[i][j].second-layered[i][j].second;
                }
            }
        }
    }
}


using circle = pair<pll,ll>;
ll dis(pll& a, pll& b){
    return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);
}

bool intersect(circle& a, circle& b){
    ll d=dis(a.first,b.first);
    ll maxd=(a.second+b.second)*(a.second+b.second);
    if(d <= maxd) return true;
    return false;
}

ll Q=0;
    

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll L,W,N,D;
    while(1){
        cin>>L>>W>>N>>D;
        if(L==W && W == N && N==D && D == 0) return 0;
        vector<circle> vl(N);
        for(int i=0; i<N; i++){
            cin>>vl[i].first.first;
            cin>>vl[i].first.second;
            vl[i].second=D;
        }
        ll S = 2*N;
        ll T=2*N+1;
        Dinics::clear(2*N+2);
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(i==j) continue;
                if(intersect(vl[i],vl[j])) Dinics::vadj[i+N][j]=1;
            }
        }

        for(int i=0; i<N; i++){
            if(vl[i].first.second+vl[i].second >= W) Dinics::vadj[i+N][T]=1;
            if(vl[i].first.second-vl[i].second <= 0) Dinics::vadj[S][i]=1;
        }

        for(int i=0; i<N; i++){
            Dinics::vadj[i][i+N]=1;
        }
        /*cout << "Checking Graph" << endl;
        for(int i=0; i<N; i++){ 
            cout << Dinics::vadj[i][T] << ' ';
        }
        cout << endl;
        for(int i=0; i<N; i++){
            cout << Dinics::vadj[S][i] << ' ';
        }
        cout << endl;
        cout << endl;

        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                cout << Dinics::vadj[i][j] << ' ';
            }
            cout << endl;
        } */

        ll mf = Dinics::dinics(2*N+2,S,T);
        /*
        if(Q==121){
            cout << L << ' ' << W << ' ' << N << ' ' << D << endl;
            for(int i=0; i<N; i++){
                cout <<vl[i].first.first << ' ' << vl[i].first.second<<endl;
            }
        }*/
        cout << "Case " << ++Q << ": " << mf << '\n';
    }
}
        



#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=1e5+7;

namespace SparseLCA{
    const int maxPow = 30;
    ll f1[maxn];
    ll depth[2*maxn];
    ll depthAns[2*maxn];
    ll cc=0;
    ll dpVal[2*maxn][maxPow];
    ll dpAns[2*maxn][maxPow];

    void build(int x, int p, int d, vll vadj[maxn]){
        f1[x]=cc;
        depth[cc]=d;
        depthAns[cc]=x;
        cc++;
        for(ll y: vadj[x]){
            if(y==p) continue;
            build(y,x,d+1,vadj);
            depth[cc]=d;
            depthAns[cc]=x;
            cc++;
        }
    }

    void buildPow(ll N){
        for(int i=0; i<(2*N-1); i++){
            dpAns[i][0]=depthAns[i];
            dpVal[i][0]=depth[i];
        }
        for(int j=1; j<maxPow; j++){
            for(int i=0; i<(2*N-1); i++){
                dpAns[i][j]=dpAns[i][j-1];
                dpVal[i][j]=dpVal[i][j-1];
                int nex = i+(1<<(j-1));
                if(nex >= 2*N-1) continue;
                if(dpVal[nex][j-1] < dpVal[i][j]){
                    dpVal[i][j]=dpVal[nex][j-1];
                    dpAns[i][j]=dpAns[nex][j-1];
                }
            }
        }
    }

    ll query(ll a, ll b){
        ll pa = f1[a];
        ll pb = f1[b];
        ll fa = min(pa,pb); ll fb = max(pa,pb);
        ll dis = fb-fa+1;
        ll pp = 63-__builtin_clzll(dis);
        ll nex = fb-(1<<pp)+1;
        ll ans = dpAns[fa][pp];

        /*
        cout << "Query: " << a+1 << ' ' << b+1 << endl;
        cout << fa << ' ' << fb << endl;
        cout << dis << endl;
        cout << nex << ' ' << pp << endl;
        cout << "End Query" << endl;
        */
        if(dpVal[nex][pp] < dpVal[fa][pp]) return dpAns[nex][pp];
        return ans;
    }

    void preprocess(ll x, ll N, vll vadj[maxn]){
        cc=0;
        build(x,x,0,vadj);
        buildPow(N);
    }
}


ll costDown[maxn];
ll costUp[maxn];
vll vadj[maxn];
vpll dd[maxn];
vpll uu[maxn];

void DFS(ll x, ll p, ll c, ll cost[maxn], vpll adj[maxn]){
    cost[x]=c;
    for(pll yy: adj[x]){
        int y=yy.first;
        if(y == p) continue;
        DFS(y,x,yy.second+c,cost,adj);
    }
}

                
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll T; cin>>T;
    auto clear = [&](int N){
        for(int i=0; i<N; i++){
            uu[i].clear();
            dd[i].clear();
            vadj[i].clear();
        }
    };
    while(T--){
        ll N; cin>>N; 
        clear(N);
        ll ans=0;
        for(int i=1; i<N; i++){
            ll a,b,c,d;
            cin>>a>>b>>c>>d;
            a--; b--;
            ans+=c;
            ans+=d;
            vadj[a].push_back(b);
            vadj[b].push_back(a);
            dd[a].push_back({b,c});
            uu[a].push_back({b,d});
            dd[b].push_back({a,d});
            uu[b].push_back({a,c});
        }
        DFS(0,0,0,costDown,dd);
        DFS(0,0,0,costUp,uu);
        SparseLCA::preprocess(0,N,vadj);
        /*
        cout << "INDEXES:" << endl;
        for(int i=0; i<2*N-1; i++){
            cout << SparseLCA::depthAns[i] << ' ';
        } 
        cout << "END DEPTHS" << endl;
        cout << "DEPTHS:" << endl;
        for(int i=0; i<2*N-1; i++){
            cout << SparseLCA::depth[i] << ' ';
        } 
        cout << "END DEPTHS END" << endl;
        cout << "SPARSE TABLE:" << endl;
        for(int i=0; i<2*N-1; i++){
            for(int j=0; j<4; j++){
                cout << SparseLCA::dpAns[i][j] << ' ';
            }
            cout << endl;
        }
        cout << "SPARSE TABLE END" << endl;*/
        ll Q; cin>>Q;
        auto lca_x = [&](int lca, int x){
            return costDown[x]-costDown[lca];
        };
        auto x_lca = [&](int x, int lca){
            return costUp[x]-costUp[lca];
        };
        while(Q--){
            ll a,b; cin>>a>>b;
            a--; b--;
            ll lca = SparseLCA::query(a,b);
            //cout << "LCA: " << lca+1 << endl;
            cout << ans-lca_x(lca,a)-x_lca(b,lca) << '\n';
        }
    }
}

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 1e5+2;

namespace RangeLCA{
    const int maxPow = 30;
    int cc = 0;
    int depthIn[maxn*2];
    int depthIndex[maxn*2];
    int firstDFS[maxn];
    int dpVal[maxn*2][maxPow];
    int dpAns[maxn*2][maxPow];

    void clear(int N){
        cc = 0;
    }


    void build(int x, int p, int d, vector<vll>& vadj){ // first clear, then build
        firstDFS[x] = cc;
        depthIn[cc] = d;
        depthIndex[cc] = x;
        cc++;
        for(int y: vadj[x]){
            if(y == p) continue;
            build(y,x,d+1,vadj);
            depthIn[cc] = d;
            depthIndex[cc] = x;
            cc++;
        }
    }

    void build(int x, int N,vector<vll>& vadj){
        clear(N);
        build(x,x,0,vadj);
        for(int j=0; j<maxPow; j++){
            for(int i=0; i<2*N-1; i++){
                if(j == 0){
                    dpVal[i][j] = depthIn[i];
                    dpAns[i][j] = depthIndex[i];
                    continue;
                }
                ll indexNext = i+(ll(1)<<(j-1));
                if(indexNext >= 2*N-1 || dpVal[i][j-1] <  dpVal[indexNext][j-1]){
                    dpVal[i][j] = dpVal[i][j-1];
                    dpAns[i][j] = dpAns[i][j-1];
                    continue;
                }
                dpVal[i][j] = dpVal[indexNext][j-1];
                dpAns[i][j] = dpAns[indexNext][j-1];
            }
        }
        /*cout << "DEPTH:" << endl;
        for(int i=0; i<2*N-1; i++){
            cout << depthIndex[i] << ' ' ;
        }
        cout << endl;
        for(int i=0; i<2*N-1; i++){
            cout << depthIn[i] << ' ' ;
        }
        cout << endl; */
    }

    int lca(int a, int b){
        int fa = min(firstDFS[a],firstDFS[b]);
        int fb = max(firstDFS[a],firstDFS[b]);
        int len = fb-fa+1;
        ll pp = 31-__builtin_clz(len);
        // cout << "QUERY: " << a << ' ' << b << ' ' << fa << ' ' << fb << ' ' << len << ' ' << pp << endl;
        // cout << fb-(1<<pp)+1 << endl;
        if(dpVal[fa][pp] < dpVal[fb-(1<<pp)+1][pp]) return dpAns[fa][pp];
        return dpAns[fb-(1<<pp)+1][pp];
    }
}

void getCost(int x, ll c,vector<vector<pll>>& vadjCost, vll& cost){
    cost[x] = c;
    for(pll yy : vadjCost[x]){
        getCost(yy.first, c+yy.second, vadjCost, cost);
    }
}
        
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    while(1){
        ll N; cin>>N;
        if(N == 0) return 0;
        vector<vll> vadj(N);
        vector<vector<pll>> vadjCost(N);
        for(int i=1; i<N; i++){
            ll a,b; cin>>a>>b;
            vadj[i].push_back(a);
            vadj[a].push_back(i);
            vadjCost[a].push_back({i,b});
        }

        vll cost(N);
        getCost(0,0,vadjCost,cost);
        RangeLCA::build(0,N,vadj);
        ll Q; cin>>Q;
        while(Q--){
            ll a,b; cin>>a>>b;
            int c = RangeLCA::lca(a,b);
            //cout << "LCA " << a << ' ' << b << ' ' << c << endl;
            cout << cost[a]+cost[b]-2*cost[c];
            if(Q!=0) cout << ' ';
        }
        cout << '\n';
    }
}

    

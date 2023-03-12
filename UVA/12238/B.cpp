#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 1e5+2;

namespace OffLineLCA{
    int vl[maxn];
    vll q[maxn];
    int marked[maxn];
    map<pll,ll> mp;

    void clear(int N){
        mp.clear();
        for(int i=0; i<N; i++) q[i].clear();
    }

    
    int find(ll x){
        if(vl[x] == x) return vl[x];
        return vl[x] = find(vl[x]);
    }

    void un(ll a, ll b){ //pa becomes head
        ll pa = find(a);
        ll pb = find(b);
        vl[pb] = pa;
    }

    void DFS(int x, ll p, vector<vll>& vadj){
        marked[x] = 1;
        vl[x] = x;
        for(int y: q[x]){
            if(marked[y]){
                ll m = min(x,y);
                ll n = max(x,y);
                mp[pll(m,n)] = find(y);
            }
        }

        for(int y: vadj[x]){
            if(p == y) continue;
            DFS(y,x,vadj);
            un(x,y);
        }
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
        OffLineLCA::clear(N);
        ll Q; cin>>Q;
        vpll queries(Q);
        for(int i=0; i<Q; i++){
            ll a,b; cin>>a>>b;
            queries[i].first = min(a,b);
            queries[i].second = max(a,b);
            OffLineLCA::q[a].push_back(b);
            OffLineLCA::q[b].push_back(a);
        }
        OffLineLCA::DFS(0,0,vadj);
        for(int i=0; i<Q; i++){
            int c = OffLineLCA::mp[pll(queries[i].first,queries[i].second)];
            ll ans = cost[queries[i].first] + cost[queries[i].second] - 2*cost[c];
            cout << ans << (i == Q-1 ? '\n' : ' ');
        }
    }
}

    

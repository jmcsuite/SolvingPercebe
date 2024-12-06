#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const long long maxn = 100000;

namespace Tarjan{
    ll low[maxn];
    ll hi[maxn];
    ll cont = 0;
    vector<multiset<ll>> vadj;
    set<pll> bridge;

    void dfs(ll x){
        low[x] = hi[x] = ++cont;
        for(auto y : vadj[x]){
            if(hi[y] == 0){
                vadj[y].erase(vadj[y].find(x));
                dfs(y);
                low[x] = min(low[x], low[y]);
                vadj[y].insert(x);
            }
            low[x] = min(low[x], hi[y]);
            if(hi[x] < low[y]) bridge.insert({x,y});
        }
    }
}

ll vl[maxn];

ll find(ll x){
    return (vl[x] == x ? x : vl[x] = find(vl[x]));
}

void Union(ll a, ll b){
    ll pa = find(a);
    ll pb = find(b);
    vl[pa] = pb;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M, Q;
    cin>>N>>M>>Q;
    for(int i=0; i<N; i++) vl[i]=i;
    Tarjan::vadj.resize(N);
    
    for(int i=0; i<M; i++){
        ll a,b; cin>>a>>b; a--; b--;
        if(a == b){
            while(1){
                a++;
            }
        }
        Tarjan::vadj[a].insert(b);
        Tarjan::vadj[b].insert(a);
    }
    Tarjan::dfs(0);

    for(auto p : Tarjan::bridge){
        Union(p.first, p.second);
    }

    for(int i=0 ; i<Q; i++){
        ll a,b; cin>>a>>b; a--; b--;
        ll pa = find(a);
        ll pb = find(b);
        if(pa == pb) cout << "YES\n";
        else cout << "NO\n";
    }
}


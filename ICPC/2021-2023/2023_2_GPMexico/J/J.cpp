#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn = 1e5;

namespace Tarjan{
    ll lo[maxn];
    ll hi[maxn];
    ll cc=0;
    vector<multiset<ll>> vadj;
    ll invalid[maxn];

    void dfs(ll x){
        lo[x] = hi[x] = ++cc;
        for(ll y : vadj[x]){
            if(hi[y]==0){
                vadj[y].erase(vadj[y].find(x));
                dfs(y);
                vadj[y].insert(x);
            }
            lo[x] = min(lo[x], lo[y]);
            if(hi[x] >= lo[y]) invalid[x]=1;
        }
    }
}

ll comp[maxn];
ll myc=0;

void dfs(ll x){
    if(comp[x]) return;
    if(Tarjan::invalid[x]) return;
    comp[x]=myc;
    for(ll y : Tarjan::vadj[x]) dfs(y);
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M,Q; cin>>N>>M>>Q;
    Tarjan::vadj.resize(N);
    for(int i=0; i<M; i++){
        ll a,b; cin>>a>>b; a--; b--;
        Tarjan::vadj[a].insert(b);
        Tarjan::vadj[b].insert(a);
    }

    Tarjan::dfs(0);
    for(int i=0; i<N; i++){
        if(comp[i]) continue;
        myc++;
        if(Tarjan::invalid[i]) comp[i]=myc;
        dfs(i);
    }

    for(int i=0; i<Q; i++){
        ll a,b; cin>>a>>b; a--; b--;
        if(comp[a] == comp[b]) cout << "YES\n";
        else cout << "NO\n";
    }
}

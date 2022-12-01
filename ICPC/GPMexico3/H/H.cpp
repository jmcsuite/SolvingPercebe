#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = (a); i<(b); i++)
using namespace std;
using ll = long long;
using vll = vector<ll>;

namespace scc{
    const int maxn=1e4+5;
    int num[maxn],cc[maxn],s[maxn],v,NUM,ncc,sz[maxn];
    vector<int> ady[maxn]; unordered_set<int> dag[maxn];
    void clear(int n) {rep(i,0,n) num[i]=0,cc[i]=-1,ady[i].clear(); NUM=ncc=0;}
    int dfs(int x){
        int lo=num[x]=++NUM; s[v++]=x;
        for(int y:ady[x]) if(cc[y]<0) lo=min(lo,num[y]?:dfs(y));
        if(num[x]==lo) {
            // reduce la gráfica a una dag, x pertenece a cc[x], x colapsa sz[x] nodos
            cc[x]=ncc++,dag[cc[x]].clear(),sz[cc[x]]=0;
            for(int y=-1;y!=x;) {
                cc[y=s[--v]]=cc[x];
                sz[cc[x]]++;
                for(int z:ady[y]) if(cc[z]!=cc[x]) dag[cc[x]].insert(cc[z]);
            }
        }
        return lo;
    }
    void tarjan(int n){rep(i,0,n) if(cc[i]<0) dfs(i);}
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    scc::clear(N);
    for(int i = 0; i < M; i++){
        ll a,b; cin>>a>>b;
        a--; b--;
        scc::ady[a].push_back(b);
    }
    scc::tarjan(N);
    ll S = scc::ncc;
    vll in(S);
    vll out(S);
    for(int i = 0; i<S; i++){
        auto it = scc::dag[i].begin();
        while(it != scc::dag[i].end()){
            out[i]++;
            in[*it]++;
            it++;
        }
    }

    ll leaves = 0;
    ll roots = 0;
    for(int i = 0; i<S; i++){
        if(in[i] == 0) roots++;
        if(out[i] == 0) leaves++;
    }
    if(S == 1){
        cout << 0 << '\n';
        return 0;
    }
    cout << max(roots, leaves) << '\n';
}


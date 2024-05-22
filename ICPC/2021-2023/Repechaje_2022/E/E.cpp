#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll, ll>;
using vpll = vector<pll>;


namespace scc{
    const int maxn=2e5+5;
    int num[maxn], cc[maxn],s[maxn],v,NUM,ncc,sz[maxn];
    vector<int> ady[maxn]; unordered_set<int> dag[maxn];
    void clear(int n) {for(int i=0;i<n;i++)  num[i]=0,cc[i]=-1,ady[i].clear(); NUM=ncc=0;}
    int dfs(int x){
        int lo=num[x]=++NUM; s[v++]=x;
        for(int y:ady[x]) if(cc[y]<0) lo=min(lo, num[y]?:dfs(y));
        if(num[x]==lo) {
            cc[x]=ncc++,dag[cc[x]].clear(),sz[cc[x]]=0;
            for(int y=-1;y!=x;)  {
                cc[y=s[--v]] = cc[x];
                sz[cc[x]]++;
                for(int z:ady[y]) if(cc[z]!=cc[x]) dag[cc[x]].insert(cc[z]);
            }
        }
        return lo;
    } 
    void tarjan(int n){
        for(int i = 0; i < n; i++) if(cc[i]<0) dfs(i);}
}
                
void dfs(ll i, ll j, vector<vector<vpll>>& vadj, vector<vll>& vis, vector<vll>& cant){
    if(vis[i][j]) return;
    vis[i][j] = 1;
    cant[i][j] = -1;
    for(int k = 0; k < vadj[i][j].size(); k++){
        dfs(vadj[i][j][k].first, vadj[i][j][k].second, vadj, vis, cant);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, M; cin >> N >> M;
    vector<vector<vpll>> vadj(N);
    for(int i = 0; i < N; i++) vadj[i].resize(2);
    vector<vector<vpll>> vadj2(N);
    for(int i = 0; i < N; i++) vadj2[i].resize(2);
    vector<vll> cant(N);
    for(int i = 0; i < N; i++) cant[i].resize(2); 
    vector<vll> vis(N);
    for(int i = 0; i < N; i++) vis[i].resize(2);
    function< void(string&, int, int, int)> func = [&](string& s, int x, int a, int b){
        if(x == 0 && s == "="){
           cant[a][1] = -1;
           cant[b][1] = -1;
        }
        if(s == "=" && x == 2){
           cant[a][0] = -1;
           cant[b][0] = -1;
        }
        if(s == "=" && x == 1){
            vadj[a][0].push_back(pll(b,1));
            vadj[b][0].push_back(pll(a,1));
            vadj[b][1].push_back(pll(a,0));
            vadj[a][1].push_back(pll(b,0));
        }
        if(s == "!=" && x == 2){
            vadj[a][1].push_back(pll(b,0));
            vadj[b][1].push_back(pll(a,0));
        }
        if(s == "!=" && x == 0){
            vadj[a][0].push_back(pll(b,1));
            vadj[b][0].push_back(pll(a,1));
        }
        if(s == "!=" && x == 1){
            vadj[a][0].push_back(pll(b,0));
            vadj[b][0].push_back(pll(a,0));
            vadj[a][1].push_back(pll(b,1));
            vadj[b][1].push_back(pll(a,1));
        }
        string ig = "=";
        string noig = "!=";
        if(s == ">" && x == 1){
            func(ig,2, a, b);
        }
        if(s == "<" && x == 1){
            func(ig, 0, a, b);
        }
        if(s == ">" && x == 2){
            func(ig, 0, a, b);
            func(ig, 2, a, b);
        }
        if(s == "<" && x == 0){
            func(ig, 0, a, b);
            func(ig, 2, a, b);
        }
        if(s == ">" && x == 0){
            func(noig, 0, a, b);
        }
        if(s == "<" && x == 2){
            func(noig, 2, a, b);
        }
        if(s == ">=" && x == 2){
            func(ig, x, a, b);
        }
        if(s == ">=" && x == 1){
            func(noig, 0, a, b);
        }
        if(s == "<=" && x == 0){
            func(ig, x, a, b);
        }
        if(s == "<=" && x == 1){
            func(noig, 2, a, b);
        }
    };
    for(int i = 0; i < M; i++){
        ll a,b; string ss; ll c;
        cin >> a >> b >> ss >> c;
        func(ss,c,a,b);
    }
    scc::clear(2*N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < vadj[i][j].size(); k++){
                scc::ady[i*2+j].push_back(vadj[i][j][k].first*2+vadj[i][j][k].second);
                vadj2[vadj[i][j][k].first][vadj[i][j][k].second].push_back(pll(i,j));
            }
        }
    }
    scc::tarjan(2*N);

    for(int i = 0; i < N; i++){
        for(int j = 0; j < 2; j++){
            if(!vis[i][j] && (cant[i][j] == -1)) dfs(i,j, vadj2, vis, cant);
        }
    }
        
    bool ans = true;
    for(int i = 0; i < N; i++){
        if(scc::cc[i*2] == scc::cc[i*2+1]) ans = false;
        if(cant[i][0] == -1 && cant[i][1] == -1) ans = false;
    }

    cout << (ans ? "Yes" : "No") << '\n';
    
}

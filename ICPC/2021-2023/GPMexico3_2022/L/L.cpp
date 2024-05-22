#include <bits/stdc++.h>
#define rep(i,a,b) for(ll i = (a); i < (b); i++)
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
const int maxn = 1e5+3;



ll d[maxn], vis[maxn], q[maxn],s,e,k,p[maxn];
ll color[maxn];
vector<ll> colorTrans[maxn];

const int L=20;
vector<ll> ady[maxn];

ll P[L][maxn], D[maxn];

void bfs(vector<ll> us) {
    s=e=0; k++;
    for(ll u : us)
        d[u]=0,p[u]=u,vis[u]=k,q[e++]=u;
    while(s<e) {
        ll u=q[s++];
        for(auto v: ady[u]) if(vis[v]!=k)
            d[v]=d[u]+1, p[v]=u, vis[v]=k, q[e++]=v;
    }
}

ll query_binlift(ll u, ll v) {
    if(D[u] > D[v]) swap(u,v);
    for(ll i=L-1; i>=0; i--) if(D[u] <= D[P[i][v]]) v=P[i][v];
    for(ll i=L-1; i>=0; i--) if(P[i][u] != P[i][v]) u=P[i][u], v=P[i][v];
    return u == v ? u : P[0][u];
}
void build_binlift(ll x, ll n) {
    bfs({x});
    rep(i,1,n+1) P[0][i]=p[i], D[i]=d[i];
    rep(i,1,L) rep(j,1,n+1) P[i][j]=P[i-1][P[i-1][j]];
}


void DFS(ll x, ll px){
    colorTrans[color[x]].push_back(x);
    for(size_t i = 0; i < ady[x].size(); i++){
        if(px == ady[x][i]) continue;
        DFS(ady[x][i], x);
    }
}

unordered_set<int> resets[maxn];
ll ccAll[maxn];
ll forAll[maxn];
ll for2[maxn];

map<pll, ll> ans;
void DFS_Reset(ll x, ll px){
    unordered_map<ll,ll> mp;
    unordered_map<ll,ll> mp2;
    for(auto it = resets[x].begin(); it != resets[x].end(); it++){
        mp[*it] = forAll[*it];
        forAll[*it] = 0;

        mp2[*it] = for2[*it];
        for2[*it] = 0;
    }

    for(size_t i = 0; i < ady[x].size(); i++){
        if(ady[x][i] == px) continue;
        DFS_Reset(ady[x][i], x);
    }
    forAll[color[x]]++;
    ll kek = 0;
    for(auto it=resets[x].begin(); it != resets[x].end(); it++){
        ll pp = forAll[*it];
        forAll[*it] += mp[*it];
        kek += (pp*(pp-1))-for2[*it];
        for2[*it] = mp2[*it]+(pp*(pp-1));
    }
    ccAll[x] = kek*ll(-1);
}


ll DFS_Ans(ll x, ll px){
    for(size_t i = 0; i < ady[x].size(); i++){
        if(ady[x][i] == px) continue;
        ll a = DFS_Ans(ady[x][i], x);
        ans[pll(x,ady[x][i])] += a;
        ans[pll(ady[x][i],x)] += a;
        ccAll[x] += a;
    }
    return ccAll[x];
}





int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    for(int i = 1; i  <= N; i++) cin>>color[i];
    vector<pll> edges;
    edges.resize(N-1);
    for(int i = 0; i < N-1; i++){
        ll a,b; cin>>a>>b;
        ady[a].push_back(b);
        ady[b].push_back(a);
        edges[i].first = a;
        edges[i].second = b;
    }
    DFS(1,1);
    build_binlift(1,N);
    for(int i = 0; i < maxn; i++){
        for(size_t j = 1; j < colorTrans[i].size(); j++){
            //cout << i << ' ' << colorTrans[i][j] << ' ' << colorTrans[i][j-1] << endl;
            ll pa = query_binlift(colorTrans[i][j], colorTrans[i][j-1]);
            //cout << i << ' ' << colorTrans[i][j] << ' ' << colorTrans[i][j-1] << ' ' << pa << endl;
            resets[pa].insert(i);
        }
    }
    DFS_Reset(1,1);
    for(int i = 1; i < N+1; i++){
        ll pp = color[i];
        ccAll[i] += forAll[pp];
        ccAll[i]--;
        //cout << i << ' ' << forAll[pp] << endl;
    }
    DFS_Ans(1,1);
    for(int i = 0; i < N-1; i++){
        ll xx = ans[edges[i]];
        cout << xx << (i == N-2 ? '\n' : ' ');
    }
    
}
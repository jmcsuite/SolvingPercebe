#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 3e5+1;
vll vadj[maxn];
ll N,M;

int vis[maxn];

void DFS(ll x){
    if(x == N-1) return;
    if(vis[x]) return;
    vis[x] = 1;
    for(int i=0; i<vadj[x].size(); i++){
        DFS(vadj[x][i]);
    }
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M;
    for(int i=0; i<M; i++){
        ll a,b; cin>>a>>b;
        a--; b--;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }
    DFS(N-2);
    for(int i=0; i<N; i++){
        if(vis[i]) cout << "B";
        else cout << "A";
    }
    cout << '\n';
}
    

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=100000;

ll C[maxn];
ll S[maxn];
ll F[maxn];

vll vadj[maxn];
ll vis[maxn];
ll vis2[maxn];

bool expand(ll N){
    queue<ll> q;
    set<ll> k;
    set<pll> nodes;

    q.push(0);
    while(!q.empty()){
        ll x = q.front(); q.pop();
        vis[x] = 2;
        k.insert(S[x]);
        for(ll y: vadj[x]){
            if(vis[y] == 2) continue;
            if((k.find(C[y]) == k.end())) continue;
            q.push(y);
            vis[y] = 2;
        }
        pll ff = {S[x], -1}; 
        while(1){
            auto it = nodes.lower_bound(ff);
            if(it == nodes.end() || it-> first != S[x]) break;
            ll y = it->second;
            nodes.erase(it);
            if(vis[y] == 2) continue;
            q.push(y);
            vis[y] = 2;
        }

        for(ll y: vadj[x]){
            if(vis[y]) continue;
            nodes.insert({C[y], y});
            vis[y] = 1;
        }
    }
    for(int i=0; i<N; i++){ 
        if(vis[i] == 1) vis[i] = 0;
        if(vis[i] == 2) vis[i] = 1;
    }
    for(int i=0; i<N; i++){
        if(vis[i] == 0 && (F[i] != S[i])) return false;
    }
    return true;
}

            
bool reduce(ll N){
    queue<ll> q;
    set<ll> k;
    set<pll> nodes;

    q.push(0);
    while(!q.empty()){
        ll x = q.front(); q.pop();
        vis[x] = 2;
        k.insert(F[x]);
        for(ll y: vadj[x]){
            if(vis[y] == 2) continue;
            if(vis[y] == 0) continue;
            if((k.find(C[y]) == k.end()) && (C[y] != F[y])) continue;
            q.push(y);
            vis[y] = 2;
        }
        pll ff = {F[x], -1}; 
        while(1){
            auto it = nodes.lower_bound(ff);
            if(it == nodes.end() || it-> first != F[x]) break;
            ll y = it->second;
            nodes.erase(it);
            if(vis[y] == 2) continue;
            q.push(y);
            vis[y] = 2;
        }

        for(ll y: vadj[x]){
            if(vis[y] == 0) continue;
            if(vis[y] == 2) continue;
            if(vis[y] == 3) continue;
            nodes.insert({C[y], y});
            vis[y] = 3;
        }
    }
    for(int i=0; i<N; i++){
        if(vis[i] == 1 || vis[i] == 3) return false;
    }
    return true;
}
            


int main(){
    ll T; cin>>T;
    while(T--){
        ll N,M;
        cin>>N>>M;
        for(int i=0; i<N; i++) vadj[i].clear();
        for(int i=0; i<N; i++) vis[i]=0;
        for(int i=0; i<N; i++) vis2[i]=0;
        for(int i=0; i<N; i++) cin>>C[i];
        for(int i=0; i<N; i++) cin>>S[i];
        for(int i=0; i<N; i++) cin>>F[i];
        for(int i=0; i<M; i++){
            ll a,b; cin>>a>>b; a--; b--;
            vadj[a].push_back(b);
            vadj[b].push_back(a);
        }

        bool ans = expand(N);
        if(!ans){
            cout << "NO\n";
            continue;
        }
        ans = reduce(N);
        if(!ans){
            cout << "NO\n";
            continue;
        }
        cout << "YES\n";
    }
}


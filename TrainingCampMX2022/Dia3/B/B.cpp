#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M;
    cin>>N>>M;
    vector<vpll> vadj(N);
    for(int i = 0; i < M; i++){
        ll a,b,c; cin>>a>>b>>c;
        vadj[a].push_back(pll(b,c));
        vadj[b].push_back(pll(a,c));
    }

    ll P; cin>>P; vll pol(P);
    for(int i = 0; i < P; i++) cin>>pol[i];
    ll Q; cin>>Q; vll esp(Q);
    for(int i = 0; i < Q; i++) cin>>esp[i];

    ll S, D; cin>>S>>D;
    vll vis(N,1e17);
    priority_queue<pll> pq;
    pq.push(pll(D,0));
    
    while(!pq.empty()){
        auto p = pq.top();
        pq.pop();
        int node = p.first;
        ll t = p.second;
        if(vis[node] < t) continue;
        vis[node] = t;
        for(size_t i = 0; i < vadj[node].size(); i++){
            ll nex = vadj[node][i].first;
            ll ti = vadj[node][i].second+t;
            if(vis[nex] <= ti) continue;
            vis[nex] = ti;
            pq.push(pll(nex,ti));
        }
    }

    ll ansDDD = vis[S];
    for(int i = 0; i < N; i++) vis[i] = vis[i]*2;
    for(int i = 0; i < Q; i++){
        ll node = esp[i];
        vis[node]/=2;
        pq.push(pll(node,vis[node]));
    }
    while(!pq.empty()){
        auto p = pq.top();
        pq.pop();
        int node = p.first;
        ll t = p.second;
        if(vis[node] < t) continue;
        vis[node] = t;
        for(size_t i = 0; i < vadj[node].size(); i++){
            ll nex = vadj[node][i].first;
            ll ti = vadj[node][i].second*2+t;
            if(vis[nex] <= ti) continue;
            vis[nex] = ti;
            pq.push(pll(nex,ti));
        }
    }
    ll ans = 1e17;
    for(int i = 0; i < P; i++){
        ll node = pol[i];
        ans = min(ans, vis[node]);
    }
    if(ansDDD*2 < ans) cout << ansDDD << endl;
    else cout << -1 << endl;
}



        
    



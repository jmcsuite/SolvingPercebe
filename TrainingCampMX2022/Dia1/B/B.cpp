#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    vector<vpll> vadj(N);
    vector<unordered_set<ll>> mp(N);
    for(int i = 0; i < M; i++){
        ll a,b,c;
        cin>>a>>b>>c;
        a--; b--;
        vadj[a].push_back(pll(b,c));
        vadj[b].push_back(pll(a,c));
    }

    vll vis(N, 1e17);
    for(int i = 0; i < N; i++){
        ll xx; cin >> xx;
        for(int j = 0; j < xx; j++){
            ll b; cin>>b;
            mp[i].insert(b);
        }
    }

    priority_queue<pll> pq;
    pq.push(pll(0,0));
    while(!pq.empty()){
        auto x = pq.top();
        pq.pop();
        ll node = x.first;
        ll t = x.second;
        if(vis[node] < t) continue;
        while(mp[node].find(t) != mp[node].end()){
            t++;
        }
        for(size_t i = 0; i < vadj[node].size(); i++){
            ll t2 = vadj[node][i].second + t;
            ll nex = vadj[node][i].first;
            if(vis[nex] <= t2) continue;
            vis[nex] = t2;
            pq.push(pll(nex,t2));
        }
    }

    if(vis[N-1] == 1e17) vis[N-1] = -1;
    cout << vis[N-1] << '\n';
    
}

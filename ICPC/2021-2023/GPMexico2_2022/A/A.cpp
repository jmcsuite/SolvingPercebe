#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
ll mod = 1e9+7;
 
ll DFS(ll x, vector<vll>& vadj, vll& trade,vll& costs){
    //cout << x << ' ' << trade[x] << endl;
    if(trade[x] != -1) return (trade[x] + costs[x]);
    trade[x] = 0;
    ll ans = 0;
    for(size_t i = 0; i < vadj[x].size(); i++){
        ans = (ans + DFS(vadj[x][i], vadj, trade, costs));
    }
    trade[x] = ans;
    trade[x] = min(ll(101), ans);
    return (trade[x] + costs[x]);
}
 
int main(){
    ll N,M,K; cin >> N >> M >> K;
    vll costs(N+1);
    vll trade(N+1,-1);
    vector<vll> vadj(N+1);
    for(int i = 0; i < M; i++){
        ll a,b,c; cin >> a >> b >> c;
        costs[b] += c;
        costs[b] = min(ll(101), costs[b]);
        vadj[b].push_back(a);
    }
    trade[1] = 1;
    for(int i = 1; i <= N; i++){
        DFS(i, vadj, trade,costs);
    }
    for(int i = 1; i <= N; i++) costs[i] = min(ll(101), (costs[i] + trade[i]));
    vll ans(K+1);
    vll anz(K+1);
    ans[0] = 1;
    ll cc = 0;
    //for(int i = 1; i <= N; i++) cout << costs[i] << endl;
    for(int i = 1; i <= N; i++){
        for(ll j = 0; j + costs[i] <= K; j++) {
            cc = (ans[j]+cc)%mod;
            ans[j + costs[i]] = (ans[j] + ans[j + costs[i]])%mod;
        }
    }
    cout << cc << '\n';
}
  
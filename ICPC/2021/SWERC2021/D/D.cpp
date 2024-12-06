#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll,ll>;
using vpll = vector<pll>;


const int maxn=2e5;


set<ll> ice;
pll input[maxn];

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    ll x=0;
    for(int i=0; i<N; i++){
        ll v; cin>>v; 
        input[i].first=x;
        input[i].second=v;
        x+=100;
    }

    for(int i=0; i<M; i++){
        cin>>x;
        ice.insert(x);
    }
    ice.insert(ll(1e15)*-1);
    ice.insert(ll(1e15));
    vpll cerca;

    for(int i=0; i<N; i++){
        auto it = ice.upper_bound(input[i].first);
        auto it2 = ice.upper_bound(input[i].first); it2--;
        ll dis1 = (*it) - input[i].first;
        ll dis2 = input[i].first - (*it2);
        dis1 = min(dis1, dis2);
        cerca.push_back({input[i].first-dis1, i});
        cerca.push_back({input[i].first+dis1, i});
    }
    sort(cerca.begin(), cerca.end());
    ll ans=0;
    ll curr=0;
    ll prev = ll(1e15)*-1;
    unordered_set<ll> st;

    /*cout << "CERCA" << endl;
    for(pll x: cerca){
        cout << x.first << ' ' << x.second << '\n';
    }
    cout << "FIN CERCA" << endl;*/

    for(pll x: cerca){
        if(x.first != prev){
            ans = max(ans, curr);
            prev=x.first;
        }
        if(st.find(x.second) == st.end()){
            curr+=input[x.second].second;
            st.insert(x.second);
        }
        else{
            curr-=input[x.second].second;
            st.erase(x.second);
        }
    }

    cout << ans << '\n';
}

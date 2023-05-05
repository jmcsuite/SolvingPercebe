#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=75;
namespace Dinics{
    map<ll,pll> vadj[maxn];
    const long long maxFlow = 1e16;

    void clear(int N){
        for(int i=0; i<N; i++) vadj[i].clear();
        for(int i=0; i<N; i++) cost[i].clear();
    }

    ll sendFlow(ll N, ll S, ll T){
        vll vis(N,maxFlow);
        vll prev(N);
        set<pll> st;
        st.insert({0,S});
        vis[S]=0;

        while(!st.empty()){
            pll p = *st.begin();
            st.erase(st.begin());
            ll x = p.first;
            ll c = p.second;

            if(x == T) break;
            if(vis[x] < c) continue;
            for(auto yy: vadj[x]){
                ll y = yy.first;
                ll cos = yy.second.second;
                ll cap = yy.second.second;
                if(cap == 0) continue;
                if(vis[y] <= cos+c) continue;
                vis[y] = cos+c;
                prev[y] = x;
                st.insert({cos+c,y});
            }
        }

        st.clear();
        ll pr=prev[T];
        ll act=T;
        while(act != S){
            vadj[pr][act].first--;
            vadj[act][pr].first++;








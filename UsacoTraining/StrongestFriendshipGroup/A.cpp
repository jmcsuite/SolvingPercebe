#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=100000;
const int maxm=maxn*2;

vll vadj[maxn];
ll pr[maxn];
ll edj[maxn];
ll vl[maxn];
ll g[maxn];

ll find(ll x){
    if(x == vl[x]) return x;
    return vl[x] = find(vl[x]);
}

ll un(ll a, ll b){
    ll pa=find(a);
    ll pb=find(b);
    if(pa == pb) return g[pa];
    vl[pb] = pa;
    g[pa] += g[pb];
    return g[pa];
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M;
    cin>>N>>M;
    for(int i=0; i<N; i++) vl[i]=i;
    for(int i=0; i<N; i++) g[i] = 1;
    for(int i=0; i<M; i++){
        ll a,b; cin>>a>>b; a--; b--;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
        edj[a]++;
        edj[b]++;
    }
    set<pll> st;
    for(int i=0; i<N; i++){
        st.insert({edj[i],i});
    }
    ll sz=0;
    while(!st.empty()){
        auto it=st.begin();
        ll x = it->second;
        st.erase(it);
        sz = max(sz,edj[x]);
        pr[x] = sz;
        for(ll y: vadj[x]){
            if(pr[y] != 0) continue;
            st.erase(pll(edj[y],y));
            edj[y]--;
            st.insert({edj[y],y});
        }
    }

    priority_queue<pll> pq;
    for(int i=0; i<N; i++){
        pq.push({pr[i],i});
    }
    ll ans = 0;
    while(!pq.empty()){
        auto pp = pq.top();
        pq.pop();
        ll x = pp.second;
        for(ll y: vadj[x]){
            if(pr[y] < pr[x]) continue;
            un(x,y);
        }
        ll px= find(x);
        ans = max(ans, g[px]*pr[x]);
    }
    cout << ans << '\n';
}

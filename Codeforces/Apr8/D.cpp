#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=100000;

ll sz[maxn];
ll imp[maxn];
set<pll> ha[maxn];
ll fa[maxn];

ll vl[maxn];

vll vadj[maxn];

void build(ll x, ll p){
    sz[x] = 1;
    imp[x] = vl[x];
    fa[x] = p;
    for(ll y: vadj[x]){
        if(y == p) continue;
        build(y,x);
        sz[x] += sz[y];
        imp[x] += imp[y];
        ha[x].insert({sz[y],y*-1});
    }
}

void upd(ll x){
    if(ha[x].empty()) return;
    ll z = fa[x];
    pll temp = *ha[x].rbegin(); 
    auto last = ha[x].end();
    last--;
    ha[x].erase(last);
    ll y = temp.second*-1;
    /*if(x == 1){
        cout << "LOOK AT Y: " << y << endl;
    }*/

    sz[x] = sz[x]-sz[y];
    fa[x] = y;
    imp[x] = imp[x]-imp[y];

    sz[y]=sz[y]+sz[x];
    imp[y] = imp[y]+imp[x];
    fa[y]=z;
    ha[y].insert({sz[x],x*-1});

    ha[z].erase({sz[y],x*-1});
    ha[z].insert({sz[y],y*-1});

}



int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    for(int i=0; i<N; i++) cin>>vl[i];
    for(int i=0; i<N-1; i++){
        ll a,b; cin>>a>>b;
        a--; b--;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }

    build(0,0);
    for(int i=0; i<M; i++){
        ll a,b; cin>>a>>b; b--;
        if(a == 2){
            upd(b); 
            continue;
        }
        cout << imp[b] << '\n';
    }
}

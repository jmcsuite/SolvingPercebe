#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn = 1e5+8;
ll food[maxn];
ll upEdge[maxn]; //va a mi padre
ll downEdge[maxn]; // va a mi
ll dpVal[maxn];
ll dpAns[maxn];

ll ans = 0;
ll lca,v,val;

ll N;

void build(ll x, bool recurse){
    if(x > N) return;

    dpVal[x] = maxn;
    dpAns[x] = -1;
    if(food[x]){
        dpVal[x] = 0;
        dpAns[x] = x;
    }

    ll child = x*2;
    for(int i=0; i<2; i++){
        if(child <= N){
            if(recurse) build(child,recurse);
            ll edgeSum = 0;

            if(downEdge[child]) edgeSum--;
            else edgeSum++;

            if(dpVal[child]+edgeSum < dpVal[x]){
                dpVal[x] = dpVal[child] + edgeSum;
                dpAns[x] = dpAns[child];
            }
        }
        child++;
    }
}

void find(ll u){
    val=maxn;
    lca=-1;
    v=-1;
    ll edgeSum = 0;

    while(u){
        if(dpVal[u]+edgeSum < val){
            val = dpVal[u]+edgeSum;
            lca = u;
            v = dpAns[u];
        }
        if(upEdge[u]) edgeSum--;
        else edgeSum++;
        u /= 2;
    }
}

void update(ll uu, ll vv, ll lc){
    ll u = uu;
    food[v]--;
    while(uu != lc){
        if(upEdge[uu]) upEdge[uu]--;
        else downEdge[uu]++;
        uu/=2;
    }
    while(vv != lc){
        if(downEdge[vv]) downEdge[vv]--;
        else upEdge[vv]++;
        vv/=2;
    }
    uu = u;
    vv = v;
    while(uu){
        build(uu, false);
        uu/=2;
    }
    while(vv){
        build(vv, false);
        vv/=2;
    }
}

int main(){
    freopen("mole.in", "r", stdin);
    freopen("mole.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll Q; cin>>N>>Q;
    for(int i=1; i<=N; i++) cin>>food[i];
    build(1,true);

    /* cout << "Build" << endl;
    for(int i=1; i<=N; i++) cout << dpAns[i] << ' ';
    cout << endl;
    for(int i=1; i<=N; i++) cout << dpVal[i] << ' ';
    cout << endl;
    cout food[v]--;<< "End build" << endl; */

    for(int i=0; i<Q; i++){
        ll a; cin>>a;
        find(a);
        ans+=val;
        cout << ans << (i == Q-1 ? '\n' : ' ');
        update(a,v,lca);
        //cout << endl;
     //   cout << v << ' ' << lca << ' ' << val << endl;
    }
}


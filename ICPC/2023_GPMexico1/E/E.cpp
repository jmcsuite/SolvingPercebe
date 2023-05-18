#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const long long inf = 1000000000000000;
const int maxn=100000;

struct segmentTree{
    struct str{
        ll x;
        ll id;
        str() : x(inf), id(inf) {}
        str(ll vx, ll sid) : x(vx), id(sid) {}
    };

    str st[2*maxn];
    ll n;
    ll h;
    ll d[2*maxn];

    str merge(str& a, str& b){
        ll x = min(a.x, b.x);
        ll id = a.id;
        if(x == b.x) id = b.id;
        return {x,id};
    }

    str ifPropagated(ll idx){
        if(d[idx] == 0) return st[idx];
        ll x = st[idx].x;
        ll id = st[idx].id;
        x+=d[idx];
        return {x,id};
    }

    void apply(ll i, ll x){
        st[i].x += x;
        d[i] += x;
    }

    void build(vll& vl, vll& v2, ll sz){
        n=sz;
        h=64-__builtin_clzll(n);
        for(int i=0; i<n; i++) st[i+n] = {vl[i],v2[i]};
        for(int i=n-1; i>0; i--) st[i]=merge(st[i*2],st[i*2+1]);
    }

    void bi(ll x){
        for(x/=2; x; x/=2){
            st[x] = merge(st[x*2],st[x*2+1]);
            st[x]=ifPropagated(x);
        }
    }

    void push(ll x){
        for(int s=h; s>0; s--){
            int i=x>>s;
            if(d[i] != 0){
                apply(i*2, d[i]);
                apply(i*2+1, d[i]);
            }
            d[i]=0;
        }
    }

    void update(ll l, ll r, ll x){
        ll l0 = l+n;
        ll r0 = r+n-1;
        push(l0);
        push(r0);

        for(l+=n,r+=n; l<r; l/=2,r/=2){
            if(l%2) apply(l++,x);
            if(r%2) apply(--r,x);
        }

        bi(l0);
        bi(r0);
    }

    str query(ll l, ll r){
        push(l+n);
        push(r+n-1);
        str ansl(inf,0);
        str ansr(inf,0);
        for(l+=n,r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl = merge(ansl, st[l++]);
            if(r%2) ansr = merge(st[--r],ansr);
        }
        return merge(ansl,ansr);
    }

};
        
ll dfsPos[maxn];
ll sz[maxn];
vll vadj[maxn];

ll idx=0;

void DFS(ll x, ll p){
    dfsPos[x]=idx;
    idx++;
    for(ll y: vadj[x]){
        if(p == y) continue;
        DFS(y,x);
        sz[x] += sz[y];
    }
    sz[x]++;
}


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    vll in(N); 
    vector<bool> root(N,true);
    for(int i=0; i<N; i++) cin>>in[i];
    for(int i=0; i<N-1; i++){
        ll a,b; cin>>a>>b;
        a--; b--;
        root[b]=false;
        vadj[a].push_back(b);
    }
    ll r=0;
    for(int i=0; i<N; i++) if(root[i]) r=i;
    DFS(r,r);
    vll vl(N);
    vll v2(N);
    for(int i=0; i<N; i++){
        vl[dfsPos[i]] = in[i];
        v2[dfsPos[i]] = i;
    }

    segmentTree st; 
    st.build(vl, v2, N);
    ll ii=0;
    vll ans(N,-1);
    while(M--){
        ii++;
        ll x,a; cin>>x>>a;
        x--; 
        ll upa = a/sz[x];
        ll upb = a%sz[x];
        st.update(dfsPos[x], dfsPos[x]+sz[x], upa*-1);
        st.update(dfsPos[x], dfsPos[x]+1,  upb*-1);

        ll l = dfsPos[x];
        ll r = dfsPos[x]+sz[x];
        while(1){
            auto q = st.query(l,r);
            
            if(q.x > 0) break;
            ans[q.id] = ii;
            st.update(dfsPos[q.id], dfsPos[q.id]+1, inf);
        }
    }

    for(int i=0; i<N; i++) cout << ans[i] << '\n';
}

    

#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
const long long mod=999999433;
const long long base=31;

const int maxn=100000;
ll pw[maxn];
ll acum[maxn];
void build(){
    pw[0]=1;
    for(int i=1; i<maxn; i++) pw[i] = (pw[i-1]*base)%mod;
    acum[0]=1;
    for(int i=1; i<maxn; i++) acum[i] = (pw[i]+acum[i-1])%mod;
}

struct segmentTree{
    struct str{
        ll hash;
        ll sz;
        str() : hash(0), sz(0) {}
        str(ll h, ll s) : hash(h), sz(s) {}
    };

    str st[2*maxn];
    ll n;
    ll h;
    ll d[2*maxn];
    str merge(str& a, str& b){
        ll h = (a.hash+(b.hash*pw[a.sz])%mod)%mod;
        ll s = a.sz+b.sz;
        return {h,s};
    }

    str ifPropagated(ll idx){
        if(d[idx] == 0) return st[idx];
        ll h = (d[idx]*acum[st[idx].sz-1])%mod;
        return {h,st[idx].sz};
    }

    void apply(ll i, ll x){
        d[i]=x;
        st[i].hash = (x*acum[st[i].sz-1])%mod;
    }

    void build(vll& vl, ll sz){
        n=sz;
        h=64-__builtin_clzll(n);
        for(int i=0; i<n; i++) st[i+n] = {vl[i]-'0'+1, 1};
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
                apply(i*2+1,d[i]);
            }
            d[i]=0;
        }
    }

    //[l,r) 0-indexed
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

    //[L,r) 0-indexed
    str query(ll l, ll r){
        push(l+n);
        push(r+n-1);
        str ansl(0,0);
        str ansr(0,0);
        for(l+=n,r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl = merge(ansl,st[l++]);
            if(r%2) ansr = merge(st[--r],ansr);
        }
        return merge(ansl,ansr);
    }
};

int main(){
    build();
    ll N,A,B; cin>>N>>A>>B;
    ll M=A+B;
    vll vl(N);
    for(int i=0; i<N; i++){
        char c; cin>>c; vl[i]=c;
    }
    segmentTree st; st.build(vl,N);
    while(M--){
        ll q,a,b,c; cin>>q>>a>>b>>c;
        if(q==1){
            c++;
            st.update(a-1,b,c);
        }else{
            a--;
            ll h1 = st.query(a,b-c).hash;
            ll h2 = st.query(a+c,b).hash;
            if(h1 == h2) cout << "YES\n";
            else cout << "NO\n";
        }
    }
}

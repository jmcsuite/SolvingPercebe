#include<bits/stdc++.h>
using namespace std;
using ll = long long;

using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn=2e5+1;

struct segmentTree{
    struct str{
        ll p;
        ll s;
        str(ll a, ll b) : p(a), s(b) {}
        str() : p(0), s(0) {}
    };

    str st[2*maxn];
    ll n;

    str func(str a, str b){
        str c;
        c.s = a.s + b.s;
        c.p = max(a.p, a.s+b.p);
        return c;
    }

    void build(ll sizn, vll& vl){
        n = sizn;
        for(int i=0; i<n; i++) st[i+n] = {max(ll(0), vl[i]), vl[i]};
        for(int i=n-1; i>0; i--) st[i] = func(st[i*2], st[i*2+1]);
    }

    void upd(ll x, ll u){
        for(x+=n, st[x]= {max(ll(0),u), u}, x/=2; x; x/=2) st[x] = func(st[x*2], st[x*2+1]);
    }

    ll query(ll l, ll r){
        str ansl = {0,0};
        str ansr = {0,0};
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl=func(ansl, st[l++]);
            if(r%2) ansr=func(st[--r], ansr);
        }
        return func(ansl,ansr).p;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,Q; cin>>N>>Q;
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];

    segmentTree st;
    st.build(N,vl);

    while(Q--){
        ll q,a,b; cin>>q>>a>>b;
        a--;
        if(q == 1){
            st.upd(a,b);
            continue;
        }
        cout << st.query(a,b) << '\n';
    }
}


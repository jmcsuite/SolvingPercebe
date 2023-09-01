#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=2e5+10;

struct segmentTree{
    ll func(ll a, ll b){
        return a+b;
    }

    ll n;
    ll st[2*maxn];

    void build(ll sizn, vll& vl){
        n=sizn;
        for(int i=0; i<n; i++) st[i+n]=vl[i];
        for(int i=n-1; i>0; i--) st[i] = func(st[i*2], st[i*2+1]);
    }

    void upd(ll x, ll inc){
        for(x+=n, st[x]+=inc, x/=2; x; x/=2){
            st[x] = func(st[x*2], st[x*2+1]);
        }
    }

    ll query(ll l, ll r){
        ll ansl=0;
        ll ansr=0;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl=func(ansl,st[l++]);
            if(r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl,ansr);
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,Q; cin>>N>>Q;
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];

    segmentTree st;
    vll dum(N);
    st.build(N,dum);

    while(Q--){
        ll q; cin>>q;
        if(q==1){
            ll a,b,u; cin>>a>>b>>u;
            a--;
            st.upd(a,u);
            if(b < N) st.upd(b,u*-1);
            continue;
        }
        ll k; cin>>k;
        cout << st.query(0,k) + vl[k-1] << '\n';
    }
}

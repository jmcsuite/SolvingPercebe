#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=2e5+2;

struct segmentTree{
    using str = long long;
    str func(str a, str b){
        return min(a,b);
    }

    str st[2*maxn];
    ll n;

    void build(vll vl, int sizn){
        n=sizn;
        for(int i=0; i<n; i++) st[i+n]=vl[i];
        for(int i=n-1; i>0; i--) st[i]=func(st[i*2],st[i*2+1]);
    }

    void upd(ll x, ll u){
        for(x+=n, st[x]=u, x/=2; x; x/=2){
            st[x]=func(st[x*2],st[x*2+1]);
        }
    }

    ll query(ll l, ll r){
        str ansl = 1e9+7;
        str ansr = ansl;
        for(l+=n,r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl = func(ansl, st[l++]);
            if(r%2) ansr = func(st[--r], ansr);
        }
        return func(ansl, ansr);
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N,Q; cin>>N>>Q; 
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];
    segmentTree st;
    st.build(vl,N);

    while(Q--){
        ll q,a,b; cin>>q>>a>>b;
        a--;
        if(q==1){
            st.upd(a,b);
            continue;
        }
        cout << st.query(a,b) << '\n';
    }
}

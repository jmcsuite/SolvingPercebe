#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=2e5+3;

struct segmentTree{
    using str=long long;

    str func(str a, str b){
        return a+b;
    }

    str st[2*maxn];
    ll n;

    void build(vll& vl, int sizn){
        n = sizn;
        for(int i=0; i<n; i++) st[i+n] = vl[i];
        for(int i=n-1; i>0; i--) st[i] = func(st[i*2],st[i*2+1]);
    }

    void update(int pos, str x){
        for(pos+=n, st[pos]=x, pos/=2; pos; pos/=2){
            st[pos] = func(st[pos*2], st[pos*2+1]);
        }
    }

    // [L,R);
    str query(int l, int r){
        str ansl=0;
        str ansr=ansl;
        for(l+=n,r+=n; l<r; l/=2,r/=2){
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
    st.build(vl,N);
    while(Q--){
        ll q,a,b; cin>>q>>a>>b; a--;
        if(q==1){
            st.update(a,b);
            continue;
        }
        cout << st.query(a,b) << '\n';
    }
}

    

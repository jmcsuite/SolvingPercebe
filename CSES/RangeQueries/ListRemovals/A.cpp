#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=4e5+2;

struct segmentTree{

    ll st[2*maxn];
    ll n;

    void build(ll sizn, vll& vl){
        n = sizn;
        for(int i=0; i<n; i++) st[i+n] = vl[i];
        for(int i=n-1; i>0; i--) st[i] = st[i*2]+st[i*2+1];
    }

    void upd(ll x, ll a){
        for(x+=n, st[x]=a, x/=2; x; x/=2){
            st[x] = st[x*2] + st[x*2+1];
        }
    }

    // binary
    ll binary(ll k){
        ll idx=1;
        while(idx < n){
            if(st[idx*2] >= k) idx*=2;
            else{
                k-=st[idx*2];
                idx = idx*2 + 1;
            }
        }
        return idx-n;
    }
};


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    ll NextN = 64-__builtin_clz(N);
    NextN = 1<<NextN;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];

    vll ones(NextN, 1);
    segmentTree st;
    st.build(NextN, ones);

    for(int i=0; i<N; i++){
        ll a; cin>>a;
        ll id = st.binary(a);
        cout << vl[id] << (i == N-1 ? '\n' : ' ');
        st.upd(id, 0);
    }
}

    
    

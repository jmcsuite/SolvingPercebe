#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 4e5+2;

struct segmentTree{
    struct str{
        ll val;
        ll pos;
        str(ll a, ll b) : val(a), pos(b) {}
        str() : val(-1), pos(-1) {}
    };

    str func(str a, str b){
        str c = {a.val, a.pos};
        if(b.val > a.val){
            c.val = b.val;
            c.pos = b.pos;
        }
        return c;
    }

    ll n;
    str st[2*maxn];
    
    // gets padded vl
    void build(ll sizn, vll& vl){
        n=sizn;
        for(int i=0; i<n; i++) st[i+n] = {vl[i], i};
        for(int i=n-1; i>0; i--) st[i] = func(st[i*2], st[i*2+1]);
    }

    void upd(ll x, ll u){
        for(x+=n, st[x].val+=u, x/=2; x; x/=2){
            st[x] = func(st[x*2], st[x*2+1]);
        }
    }

    // binary
    str binary(ll k){
        ll idx=1;
        while(idx < n){
            if(st[idx].val < k) return {-1, -1};
            if(st[idx*2].val >= k) idx*=2;
            else idx = idx*2+1;
        }
        return st[idx];
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,Q; cin>>N>>Q;
    ll NextN = 64- __builtin_clzll(N);
    NextN = 1<<NextN;

    vll vl(NextN, -1);
    for(int i=0; i<N; i++) cin>>vl[i];
    N = NextN;

    segmentTree st;
    st.build(N, vl);

    while(Q--){
        ll k; cin>>k;
        segmentTree::str ans = st.binary(k);
        cout << ans.pos+1 << (Q == 0 ? '\n' : ' ');
        if(ans.pos == -1) continue;
        st.upd(ans.pos, k*-1);
    }
}


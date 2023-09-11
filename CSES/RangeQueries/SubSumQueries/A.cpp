#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 2e5+1;

struct segmentTree{
    struct str{
        ll sum;
        ll prefix;
        ll suffix;
        ll ans;
        str(ll a, ll b, ll c, ll d) : sum(a), prefix(b), suffix(c), ans(d) {}
        str() : sum(0), prefix(0), suffix(0), ans(0) {}
        str(ll a) : sum(a), prefix(max(a,ll(0))), suffix(max(a,ll(0))), ans(max(a, ll(0))) {}
    };

    str func(str a, str b){
        ll sum = a.sum + b.sum;
        ll prefix = max(a.prefix, a.sum+b.prefix);
        ll suffix = max(b.suffix, b.sum + a.suffix);
        ll ans = a.suffix + b.prefix;
        ans = max(ans, a.ans);
        ans = max(ans, b.ans);
        return {sum, prefix, suffix, ans};
    }

    str st[2*maxn];
    ll n;

    void build(ll sizn, vll& vl){
        n = sizn;
        for(int i=0; i<n; i++) st[i+n]=vl[i];
        for(int i=n-1; i>0; i--) st[i]=func(st[i*2],st[i*2+1]);
    }

    void upd(ll x, ll v){
        for(x+=n, st[x]=v, x/=2; x; x/=2) st[x] = func(st[x*2], st[x*2+1]);
    }

    ll query(ll l, ll r){
        str ansl;
        str ansr;
        for(l+=n, r+=n; l<r; l/=2, r/=2){
            if(l%2) ansl = func(ansl, st[l++]);
            if(r%2) ansr = func(st[--r], ansr);
        }
        return func(ansl, ansr).ans;
    }
};

int main(){
    ll N,Q; cin>>N>>Q;
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];

    segmentTree st; st.build(N, vl);
    while(Q--){
        ll x, v; cin>>x>>v;
        x--;
        st.upd(x,v);
        cout << st.query(0,N) << '\n';
    }
}

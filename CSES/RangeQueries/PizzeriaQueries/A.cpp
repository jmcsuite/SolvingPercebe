#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn=2e5+1;

struct segmentTree{
    ll st[2*maxn];
    ll n;

    void build(ll sizn, vll& vl){
        n=sizn;
        for(int i=0; i<n; i++) st[i+n]=vl[i];
        for(int i=n-1; i>0; i--) st[i]=min(st[i*2], st[i*2+1]);
    }

    void upd(ll x, ll k){
        for(x+=n, st[x]=k, x/=2; x; x/=2) st[x] = min(st[x*2], st[x*2+1]);
    }

    ll query(ll l, ll r){
        ll ans=1e9+10u;
        for(l+=n, r+=n; l<r; l/=2, r/=2){
            if(l%2) ans=min(ans, st[l++]);
            if(r%2) ans=min(st[--r], ans);
        }
        return ans;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];

    vll toN(N); for(int i=0; i<N; i++) toN[i] = vl[i]+i;

    vll fromN(N); for(int i=0; i<N; i++) fromN[i] = vl[i] + (N-1-i);

    segmentTree izq;
    izq.build(N,toN);

    segmentTree der;
    der.build(N,fromN);

    while(M--){
        ll q; cin>>q;
        if(q == 2){
            ll a; cin>>a;
            a--;
            ll ans = min(izq.query(a,N)-a, der.query(0,a)-(N-1-a));
            cout << ans << '\n';
            continue;
        }
        ll x, p; cin>>x>>p;
        x--;
        izq.upd(x,p+x);
        der.upd(x, p + N-1-x);
    }
}

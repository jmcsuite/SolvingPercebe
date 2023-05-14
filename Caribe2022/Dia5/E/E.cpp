#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxc=1000002;
const int maxn=200000;
const long long mod=1000000007;

ll crib[maxc];

void build(){
    crib[1]=1;
    for(ll i=2; i<maxc; i++){
        if(crib[i] != 0) continue;
        crib[i]=i;
        for(ll j=i; j*i<maxc; j++){
            crib[i*j]=i;
        }
    }
}

vll pcount[maxc];
ll pindex[maxc];

struct segmentTree{
   using str=ll;
   str func(str a, str b){
       return (a*b)%mod;
   }
   str st[2*maxn+2];
   ll n;
   void build(vll& vl, int sizn){
       n=sizn;
       for(int i=0; i<n; i++){
           st[i+n]=vl[i];
       }
       for(int i=n-1; i>0; i--){
           if(i*2+1 > 2*n) { 
               st[i]=st[i*2];
               continue;
           }
           st[i]=func(st[i*2],st[i*2+1]);
       }
   }

   void update(int pos, str x){
       for(pos+=n, st[pos]=(st[pos]*x)%mod,pos/=2; pos; pos/=2){
           if(pos*2+1 >= 2*n) st[pos]=st[pos*2];
           else st[pos]=func(st[pos*2],st[pos*2+1]);
       }
   }

   str query(int l, int r, str def){
       str ansl=def;
       str ansr=def;
       for(l+=n,r+=n; l<r; l/=2,r/=2){
           if(l%2) ansl=func(ansl,st[l++]);
           if(r%2) ansr=func(st[--r],ansr);
       }
       return func(ansl,ansr);
   }
};

ll fact[maxc];
ll factInv[maxc];
ll inv[maxc];

ll bin_exp(ll a, ll x){
    ll ans=1;
    while(x){
        if(x%2) ans=(ans*a)%mod;
        a=(a*a)%mod;
        x/=2;
    }
    return ans;
}

using q=pair<pll,ll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    build();
    fact[0]=1;
    factInv[0]=1;
    for(int i=1; i<maxc; i++) fact[i]=(fact[i-1]*i)%mod;
    factInv[maxc-1]=bin_exp(fact[maxc-1],mod-2);
    for(int i=maxc-2; i>0; i--) factInv[i]=((i+1)*factInv[i+1])%mod;
    for(int i=1; i<maxc; i++) inv[i]=(fact[i-1]*factInv[i])%mod;

    ll N; cin>>N;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];
    segmentTree st; st.build(vl,N);

    for(int i=0; i<N; i++){
        ll x=vl[i];
        while(x>1){
            ll prev=crib[x];
            while(prev==crib[x]) x/=crib[x];
            pcount[prev].push_back(i);
        }
    }

    set<pll> myst;

    auto add = [&](ll i){
        ll j=pindex[i];
        if(j==(ll)pcount[i].size()) return;
        pindex[i]++;
        myst.insert({pcount[i][j],i});
        ll x=((i-1)*inv[i])%mod;
        st.update(pcount[i][j], x);
        return;
    };

    for(int i=2; i<maxc; i++){
        add(i);
    }

    ll Q; cin>>Q;
    vector<q> queries(Q);
    vll ans(Q);
    for(int i=0; i<Q; i++) cin>>queries[i].first.first>>queries[i].first.second;
    for(int i=0; i<Q; i++) {
        queries[i].second=i;
        queries[i].first.first--;
        queries[i].first.second--;
    }
    sort(queries.begin(),queries.end());
    for(int i=0; i<Q; i++){
        while(myst.begin() != myst.end() && myst.begin()->first < queries[i].first.first){
            ll pp=myst.begin()->second;
            myst.erase(myst.begin());
            add(pp);
        }
        ll as=st.query(queries[i].first.first,queries[i].first.second+1,1);
        ans[queries[i].second]=as;
    }
    for(int i=0; i<Q; i++) cout << ans[i] << '\n';
}

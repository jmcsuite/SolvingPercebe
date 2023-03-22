#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;

const int maxn=4194304;
const int nomaxn=1000000;
struct segmentTree{
    pll st[2*maxn];
    ll n;
    ll h;
    ll d[2*maxn];
    pll merge(pll a, pll b){
        if(a<b) return a;
        return b;
    }
    pll ifPropagated(ll idx){
        pll prev=st[idx];
        prev.first+=d[idx];
        return prev;
    }
    void build(ll sz, vll& val){
        n = maxn;
        h = 64-__builtin_clzll(maxn);
        for(int i=0; i<sz; i++){
            st[i+n].first=val[i];
            st[i+n].second=i;
        }
        for(int i=sz; i<maxn; i++){
            st[i+n].first=0;
        }
        for(int i=maxn-1; i>0; i--){
            st[i]=merge(st[i*2],st[i*2+1]);
        }
    }

    void apply(ll i, ll x){
        d[i]+=x;
        st[i].first+=x;
    }

    void bi(ll x){
        for(x/=2; x; x/=2){
            st[x] = merge(st[x*2], st[x*2+1]);
            st[x] = ifPropagated(x);
        }
    }
    
    // [l,r);
    void update(ll l, ll r, ll x){
        ll l0 = l+n;
        ll r0 = r+n-1;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) apply(l++, x);
            if(r%2) apply(--r, x);
        }
        bi(l0);
        bi(r0);
    }

    void push(ll x){
        for(int s=h; s>0; s--){
            int i = x>>s;
            if(d[i] != 0){
                apply(i*2, d[i]);
                apply(i*2+1, d[i]);
            }
            d[i]=0;
        }
    }

    pll query(){
        ll x=1;
        ll bb = 0;
        ll maxi = maxn;
        //cout << "QUERY" << endl;
        while(x < maxn){
            apply(x*2, d[x]);
            apply(x*2+1, d[x]);
            d[x]=0;

            //cout << x << ' ' << st[x].first << ' ' << d[x] << ' ' << bb << ' ' << maxi << ' ' << st[x*2].first << ' ' << st[x*2+1].first << endl; 
            if(st[x*2+1].first < 0) {
                x=x*2+1; 
                bb = (maxi+bb)/2;
            }
            else {
                x*=2;
                maxi= (maxi+bb)/2;
            }
        }
        //cout << "QUERY" << endl;
        return st[x];
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M;
    map<ll,ll> dish;
    map<ll,ll> pup;
    cin>>N>>M;
    vll vals(nomaxn+1);
    for(int i=0; i<N; i++){
        ll a; cin>>a;
        dish[i]=a;
        vals[a]--;
    }
    for(int i=0; i<M; i++){
        ll b; cin>>b;
        pup[i]=b;
        vals[b]++;
    }
    for(int i=nomaxn-1; i>=0; i--){
        vals[i]+=vals[i+1];
    }
    segmentTree st;
    st.build(nomaxn+1, vals);
    //cout << st.query().first << endl;
    ll Q; cin>>Q;
    while(Q--){
        ll a,b,c;
        cin>>a>>b>>c;
        b--;
        if(a == 1){
            ll pr = dish[b];
            st.update(0,pr+1,1);
            //add to [0,pr];
            //st.query();
            dish[b]=c;
            st.update(0,c+1,-1);
            // cout << pr << endl;
            //quita [0,c]
        }
        if(a == 2){
            ll pr = pup[b];
            // quita [0,pr]
            st.update(0,pr+1,-1);
            pup[b]=c;
            // add [0, c];
            st.update(0,c+1, +1);
        }
        pll q = st.query();
        if(q.second == 0) cout << -1 << '\n';
        else cout << q.second << '\n';
    }
}


    



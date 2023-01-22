#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
const int maxn=100002;
const int maxb=1000;
vector<int> vadj[maxn];
int order[maxn];
int sz[maxn];
int vl[maxn];
int ini[maxn];
int t;
ll N,M;

int DFS(ll x, ll px){
    int myT = t;
    t++;
    order[myT] =  x;
    ll s = 1;
    for(size_t i=0; i<vadj[x].size(); i++){
        if(vadj[x][i] == px) continue;
        s += DFS(vadj[x][i],x);
    }
    sz[myT]=s;
    return s;
}

bool isPrime(ll x){
    if(x < 2) return false;
    for(ll i=2; i*i<=x; i++){
        if(x%i==0) return false;
    }
    return true;
}

void shift(bitset<maxb>&a, int c){
    bitset<maxb> temp; temp|=a;
    temp>>=(M-c);
    a<<=(maxb-(M-c));
    a>>=(maxb-M);
    a|=temp;
}

struct segmentTree{
    bitset<maxb> st[2*maxn];
    ll n;
    ll h;
    ll d[2*maxn];
    bitset<maxb> merge(bitset<maxb>& a, bitset<maxb>& b){
        return a|b;
    }
    bitset<maxb> ifPropagated(ll idx){
        shift(st[idx], d[idx]);
        return st[idx];
    }
    void build(ll sz){
        n = sz;
        h = 64-__builtin_clzll(n);
        for(int i=0; i<n; i++){
            st[i+n].set(vl[i]%M);
        }
        for(int i=n-1; i>0; i--){
            st[i]=merge(st[i*2], st[i*2+1]);
        }
    }
    void apply(ll i, ll x){
        d[i] += x;
        d[i] %= M; 
        shift(st[i], x);
    }

    void bi(ll x){
        for(x/=2; x; x/=2){
            st[x] = merge(st[x*2], st[x*2+1]);
            st[x] = ifPropagated(x);
        }
    }

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
            int i= x>>s;
            if(d[i] != 0){
                apply(i*2, d[i]);
                apply(i*2+1, d[i]);
            }
            d[i]=0;
        }
    }

    bitset<maxb> query(ll l, ll r){
        push(l+n);
        push(r+n-1);
        bitset<maxb> ansl;
        bitset<maxb> ansr;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl = merge(ansl,st[l++]);
            if(r%2) ansr = merge(st[--r],ansr);
        }
        return merge(ansl,ansr);
    }
};




int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>N>>M;
    for(int i=0; i<N; i++) cin>>ini[i];
    for(int i=0; i<N-1; i++){
        ll a,b;
        cin>>a>>b; a--; b--;
        vadj[a].push_back(b);
        vadj[b].push_back(a);
    }
    t=0;
    DFS(0, 0);
    map<ll,ll> mp;
    for(int i=0; i<N; i++) mp[order[i]] = i;
    for(int i=0; i<N; i++) vl[i] = ini[order[i]]%M;
    segmentTree st;
    st.build(N);
    bitset<maxb> primos;
    for(int i=0; i<M; i++){
        if(isPrime(i)) primos.set(i);
    }
    ll Q;
    cin>>Q;
    
    while(Q--){
        ll k; cin>>k;
        if(k == 1){
            // update;
            ll a,b; cin>>a>>b;
            a--; b%=M;
            st.update(mp[a],mp[a]+sz[mp[a]],b);
        }else{
            ll a; cin>>a;
            a--;
            auto bs = st.query(mp[a],mp[a]+sz[mp[a]]);
            bs&=primos;
            cout << bs.count() << endl;
        }
    }
}
    
    

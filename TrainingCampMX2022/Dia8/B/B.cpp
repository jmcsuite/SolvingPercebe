#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
 
 int arrTemp[14];
void getF(ll x){
    for(int i=0; i<14; i++) arrTemp[i]=0;
    for(int i=2; i<14; i++){
        if(x%i == 0){
            arrTemp[i]++;
            x/=i;
            i--;
        }
    }
}
 
ll DFS(ll x,ll pi, vll& order, vll& si, vector<vll>& vadj){
    ll t=order.size();
    order.push_back(x);
    si.push_back(1);
    ll s =1;
    for(size_t i=0; i<vadj[x].size(); i++){
        if(vadj[x][i] == pi) continue;
        s += DFS(vadj[x][i], x, order, si, vadj);
    }
    si[t] = s;
    return s;
}

const int maxn = 1e5+1;
struct segmentTree{
    struct str{
        int val[14];
        str(){
            for(int i=0; i<14; i++) val[i]=0;
        }
        str(ll x){
            getF(x);
            for(int i=0; i<14; i++) val[i]=arrTemp[i];
        }
        void upd(ll x){
            getF(x);
            for(int i=0; i<14; i++) val[i]+=arrTemp[i];
        }
    };

    str func(str a, str b){
        for(int i=0; i<14; i++) a.val[i]+=b.val[i];
        return a;
    }
    str st[2*maxn];
    ll n;
    void build(vll& vl, int sizn){
        n = sizn;
        for(int i=0; i<n; i++){
            st[i+n].upd(vl[i]); 
        }
        for(int i=n-1; i>0; i--){
            st[i]=func(st[i*2],st[i*2+1]);
        }
    }

    void update(int pos, ll x){
        for(pos+=n,st[pos].upd(x),pos/=2;pos; pos/=2){
           st[pos] = func(st[pos*2],st[pos*2+1]);
        } 
    }

    void query(int l, int r){
        for(int i=0; i<14; i++) arrTemp[i]=0;
        str ans;
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l%2) ans=func(ans,st[l++]);
            if(r%2) ans=func(st[--r],ans);
        }
        for(int i=0; i<14; i++) arrTemp[i]=ans.val[i];
    }
};




 
ll mod=1e9+7;
ll bin_exp(ll a, ll x){
    ll ans = 1;
    while(x){
        if(x%2) ans = (ans*a)%mod;
        a = (a*a)%mod;
        x/=2;
    }
    return ans;
}
    
 
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin>>N;
    vector<vll> vadj(N);
    for(int i=0; i<N-1; i++){
        ll a,b; cin>>a>>b;
        vadj[a].push_back(b);
    }
    vll order;
    vll si;
    DFS(0,0,order, si, vadj);
    map<ll,ll> mp;
    for(int i=0; i<N; i++) mp[order[i]] = i;
    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[mp[i]];
    segmentTree st;
    st.build(vl,N);
    ll Q; cin>>Q;
    ll mod = 1e9+7; 
    while(Q--){
        string a;
        cin>>a;
        if(a == "RAND"){
            ll b; cin>>b;
            ll in = mp[b];
            ll r = in + si[in];
            st.query(in,r);
            ll ans=1;
            for(int i=0; i<14; i++){
                ans = (ans*bin_exp(i,arrTemp[i]))%mod; 
            }
            cout << ans << ' ';
            ans=1;
            for(int i=0; i<14; i++){
                ans = (ans*(arrTemp[i]+1))%mod;
            }
            cout << ans << '\n';
        }
        else{
            ll b, c;
            cin>>b>>c;
            ll in = mp[b];
            st.update(in,c);
        }
    }
}

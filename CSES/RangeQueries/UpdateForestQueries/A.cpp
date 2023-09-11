#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;


const int maxn = 1001;

struct segmentTree{

    ll n;
    ll m;
    ll st[2*maxn][2*maxn];
    ll tmp[2*maxn];

    void subBuild(vll &vl, ll n, ll k){
        for(int i=0; i<n; i++)  st[k][i+n] = vl[i];
        for(int i=n-1; i>0; i--) st[k][i] = st[k][i*2]+st[k][i*2+1];
    }

    void subUpd(ll x, ll k, ll n, ll u){
        for(x+=n, st[k][x]+=u, x/=2; x; x/=2) st[k][x]=st[k][x*2]+st[k][x*2+1];
    }

    ll subQuery(ll l, ll r, long long* tmp, ll n){
        ll ans = 0;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ans=ans+tmp[l++];
            if(r%2) ans=tmp[--r]+ans;
        }
        return ans;
    }

    void func(long long* a, long long* b, long long* c){
        for(int i=1; i<2*m; i++) c[i] = a[i]+b[i];
        //for(int i=1; i<2*m; i++) cout << c[i] << ' ' << i  << '\n';
    }

    void build(vector<vll>& vl, ll sizn, ll sizm){
        n = sizn;
        m = sizm;
        for(int i=0; i<n; i++) subBuild(vl[i], m, i+n);
        for(int i=n-1; i>0; i--) func(st[i*2], st[i*2+1], st[i]);
    }

    void upd(ll x, ll y, ll u){
        for(x+=n, subUpd(y,x,m, u), x/=2; x; x/=2) subUpd(y,x,m,u);
    }

    ll query(ll l, ll r, ll y, ll y2){
        ll ans = 0;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ans = ans + subQuery(y, y2, st[l++], m);
            if(r%2) ans = subQuery(y, y2, st[--r], m) + ans;
        }
        return ans;
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N,Q; cin>>N>>Q;
    vector<vll> vl(N); for(int i=0; i<N; i++) vl[i].resize(N);

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            char c; cin>>c; 
            if(c == '.') continue;
            vl[i][j] = 1;
        }
    }
    segmentTree st;
    st.build(vl, N, N);

    while(Q--){
        ll q; cin>>q;
        if(q == 1){
            ll a, b;
            cin>>a>>b; a--; b--;

            ll dif;
            if(vl[a][b] == 1){
                vl[a][b] = 0;
                dif=-1;
            }else{
                vl[a][b] = 1;
                dif = 1;
            }
                
        
            st.upd(a, b, dif);
            continue;
        }
        ll x, y;
        ll x2, y2; 
        cin >> x >> y >> x2 >> y2;
        x--; 
        y--;
        cout << st.query(x,x2, y , y2) << '\n';
    }
}


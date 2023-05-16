#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn=100000;
struct segmentTree{
    using str = ll;
    str func(str a, str b){
        return min(a,b);
    }

    str st[2*maxn];
    ll n;
    void build(int sizn){
        n=sizn;
        for(int i=0; i<n; i++) st[i+n]=0;
        for(int i=n-1; i>0; i--) st[i]=func(st[i*2],st[i*2+1]);
    }

    void update(int pos, str x){
        for(pos+=n,st[pos]+=x,pos/=2; pos; pos/=2){
            st[pos]=func(st[pos*2],st[pos*2+1]);
        }
    }

    str query(int l, int r){
        str ansl=maxn;
        str ansr=maxn;
        for(l+=n,r+=n;l<r;l/=2,r/=2){
            if(l%2) ansl=func(ansl,st[l++]);
            if(r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl,ansr);
    }
};

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    segmentTree st; st.build(N);
    ll mini=0;
    while(M--){
        ll x; cin>>x; x--;
        st.update(x,1);
        ll y = st.query(0,N);
        if(y>mini) cout << 1;
        if(y<=mini) cout << 0;
        if(y>mini) mini++;
    }
    cout << endl;
}


    

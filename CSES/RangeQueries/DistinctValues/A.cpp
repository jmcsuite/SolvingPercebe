#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using q = pair<pll, ll>;

const int maxn=2e5+1;

struct segmentTree{
    ll st[2*maxn];
    ll n;

    void build(ll sizn){
        n = sizn;
        for(int i=0; i<2*n; i++) st[i]=0;
    }

    void upd(ll x, ll u){
        for(x+=n, st[x]+=u, x/=2; x; x/=2) st[x]=st[x*2]+st[x*2+1];
    }

    ll query(ll l, ll r){
        ll ans=0;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ans+=st[l++];
            if(r%2) ans+=st[--r];
        }
        return ans;
    }
};

bool order(q& a, q& b){
    return a.first.first > b.first.first;
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N,Q; cin>>N>>Q;
    vll vl(N); for(int i=0; i<N; i++) cin >> vl[i];

    vector<q> vq(Q);
    for(int i=0; i<Q; i++){
        cin >> vq[i].first.first >> vq[i].first.second;
        vq[i].first.first--;
        vq[i].second=i;
    }


    vll ans(Q+1);

    for(int i=0; i<N; i++){
        vq.push_back({{i,N},Q});
    }
    sort(vq.begin(), vq.end(), order);

    map<ll,ll> prev;
    segmentTree st;
    st.build(N);

    for(q& qy: vq){
        ll x = vl[qy.first.first];
        if(prev.find(x) != prev.end()){
            st.upd(prev[x],-1);
        }
        prev[x]=qy.first.first;
        st.upd(prev[x],1);
        ans[qy.second] = st.query(qy.first.first, qy.first.second);
    }

    for(int i=0; i<Q; i++) cout << ans[i] << '\n';
}

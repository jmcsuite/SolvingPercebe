#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;


const int maxn = 6e5+2;

struct segmentTree{
    ll st[2*maxn];
    ll n;

    void build(ll sizn, vll& vl){
        n = sizn;
        for(int i=0; i<n; i++) st[i+n] = vl[i];
        for(int i=n-1; i>0; i--) st[i] = st[i*2] + st[i*2 + 1];
    }

    void upd(ll x, ll u){
        for(x+=n, st[x]+=u, x/=2; x; x/=2){
            st[x] = st[x*2] + st[x*2 + 1];
        }
    }

    // [a,b)
    ll query(ll l, ll r){
        ll ansl, ansr;
        ansl = ansr = 0;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl = ansl + st[l++];
            if(r%2) ansr = st[--r] + ansr;
        }
        return ansl + ansr;
    }
};

using pll = pair<ll,ll>;
using q = pair<ll,pll>;


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N, Q; cin>>N>>Q;
    vll vl(N); for(int i=0; i<N; i++) cin>>vl[i];

    vector<q> vq(Q);
    for(int i=0; i<Q; i++){
        char a; cin>>a; 
        if(a == '?') vq[i].first=1;
        else vq[i].first=2;
        cin>>vq[i].second.first>>vq[i].second.second;
    }

    vll allInput;
    for(int i=0; i<N; i++) allInput.push_back(vl[i]);
    for(int i=0; i<Q; i++){
        allInput.push_back(vq[i].second.second);
        if(vq[i].first == 1){
            allInput.push_back(vq[i].second.first);
        }
    }

    sort(allInput.begin(), allInput.end());
    ll idx=0;

    map<ll,ll> mp;
    mp[allInput[0]] = idx++;

    for(int i=1; i<(int)allInput.size(); i++){
        if(allInput[i] == allInput[i-1]) continue;
        mp[allInput[i]] = idx++;
    }

    vll freq(idx);
    for(int i=0; i<N; i++) vl[i] = mp[vl[i]];
    for(int i=0; i<N; i++) freq[vl[i]]++;

    segmentTree st;
    st.build(idx, freq);
    
    
    
    for(int i=0; i<Q; i++){
        if(vq[i].first == 1){
            ll a = mp[vq[i].second.first];
            ll b = mp[vq[i].second.second];
            b++;
            cout << st.query(a,b) << '\n';
            continue;
        }

        ll x = vq[i].second.first-1;
        ll valx = vl[x];
        st.upd(valx, -1);
        ll nexval = mp[vq[i].second.second];
        vl[x] = nexval;
        st.upd(nexval, 1);
    }
}

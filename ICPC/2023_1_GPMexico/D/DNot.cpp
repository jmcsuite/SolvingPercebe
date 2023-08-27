#include<bits/stdc++.h>
using namespace std;
using ll = int;
using vll = vector<ll>;
using pll = pair<ll,ll>;
using vpll = vector<pll>;
using str = int;

const int maxn = 3e6+1;

struct segmentTree{
    str func(str a, str b){
        return a+b;
    }

    str st[2*maxn];
    ll n;

    void build(vll& vl, int sizn){
        n = sizn;
        for(int i=0; i<n; i++) st[i+n] =  vl[i];
        for(int i=n-1; i>0; i--) st[i] = func(st[i*2], st[i*2+1]);
    }

    void update(int pos, str x){
        for(pos+=n,st[pos]+=x,pos/=2; pos; pos/=2){
            st[pos] = func(st[pos*2],st[pos*2+1]);
        }
    }

    //[L,R)
    str query(int l, int r){
        str ansl=0;
        str ansr=0;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl=func(ansl,st[l++]);
            if(r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl,ansr);
    }
};

using quer = pair<ll,pll>;

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);

    ll N,Q;
    cin>>N>>Q;
    
    vll all;

    vll vl(N);
    for(int i=0; i<N; i++) cin>>vl[i];
    for(int i=0; i<N; i++) all.push_back(vl[i]);

    vector<quer> vq(Q);
    for(int i=0; i<Q; i++){
        cin >> vq[i].first >> vq[i].second.first;
        all.push_back(vq[i].second.first);

        if(vq[i].first == 1) continue;
        cin >> vq[i].second.second;
        all.push_back(vq[i].second.second);
    }

    sort(all.begin(), all.end());
    ll id=0;
    map<ll,ll> mp;
    for(size_t i=0; i<all.size(); i++){
        if(i+1 == all.size() || all[i] != all[i+1]) mp[all[i]] = id++;
    }
/*
    cout << "map" << endl;
    for(auto p : mp){
        cout << p.first << ' ' << p.second << endl;
    }
*/

    for(int i=0; i<N; i++) vl[i] = mp[vl[i]];
    for(int i=0; i<Q; i++){
        vq[i].second.first = mp[vq[i].second.first];
        if(vq[i].first == 1) continue;
        vq[i].second.second = mp[vq[i].second.second];
    }

    vll freq(id);
    multiset<ll> st;
    for(int i=0; i<N; i++) freq[vl[i]]++;
    for(int i=0; i<N; i++) st.insert(vl[i]);

    segmentTree tree;
    tree.build(freq, id);

    for(int i=0; i<Q; i++){
        if(vq[i].first == 2){
            ll ans = tree.query(vq[i].second.first, vq[i].second.second+1);
            //cout << "Qans: " << i << ' ' << vq[i].second.first << ' ' <<vq[i].second.second+1 << ' ' << ans << endl;
            cout << ans << '\n';
            continue;
        }

        ll x = vq[i].second.first;
        if(st.find(x) != st.end()) continue;


        if(*st.rbegin() < x){
            st.insert(x);
            tree.update(x,1);
            continue;
        }

    

        auto it = st.upper_bound(x);

        //cout << "Qi: " << i << ' ' << x << ' ' << *it << endl;
        tree.update(*it,-1);
        st.erase(it);
        st.insert(x);
        tree.update(x,1);
    }
}

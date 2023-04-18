#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

const int maxn=200000;

struct segmentTree{
    ll func(ll a, ll b){
        return a+b;
    }
    ll st[maxn*2];
    ll n;

    void build(int sizn){
        n = sizn;
    }

    void update(int pos, ll x){
        for(pos+=n,st[pos]+=x,pos/=2; pos; pos/=2){
            st[pos] = func(st[pos*2],st[pos*2+1]);
        }
    }

    ll query(int l, int r, ll def=0){
        ll ansl=def;
        ll ansr=def;
        for(l+=n, r+=n; l<r; l/=2,r/=2){
            if(l%2) ansl=func(ansl,st[l++]);
            if(r%2) ansr=func(st[--r],ansr);
        }
        return func(ansl,ansr);
    }
};



ll s[maxn];
ll p[maxn];

pll input[maxn];


int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N,M; cin>>N>>M;
    set<pll> st;
    st.insert({0,0});
    for(int i=0; i<M; i++){
        cin>>input[i].first >> input[i].second;
        input[i].first--;
        ll x = input[i].first;
        s[x]++;
        p[x]+=input[i].second;
        st.insert({s[x],p[x]});
    }

    vector<pll> all;
    for(auto x: st){
        pll y = x;
        all.push_back(y);
    }

    sort(all.begin(), all.end(), [&](pll& a, pll& b){
            if(a.first == b.first) return a.second > b.second;
            return a < b;
            });

    map<pll,ll> mp;
    ll idx=0;
    for(pll& x: all){
        mp[x]=idx;
        idx++;
    }

    /*cout << "DEBUG ";
    for(size_t i=0; i<all.size(); i++){
        cout << all[i].first << ' ' << all[i].second << ' ' << mp[all[i]] << endl;
    }*/

    segmentTree str;
    str.build(idx);

    for(int i=0; i<N; i++) s[i]=p[i]=0;

    for(int i=0; i<M; i++){
        ll x = input[i].first;
        ll cp = p[x];
        ll cs = s[x];
        ll xId = mp[pll(cs,cp)];
        str.update(xId,-1);
        //cout << "IT: " << i << ' ' << xId << ' ';
        s[x]++;
        p[x]+=input[i].second;
        cp=p[x];
        cs=s[x];
        xId=mp[pll(cs,cp)];
        //cout << xId << ' ';
        str.update(xId, 1);

        ll fp=p[0];
        ll fs=s[0];
        ll fId=mp[pll(fs,fp)];
        //cout << fId << endl;

        cout << str.query(fId+1, idx) + 1 << '\n';
    }
}




        
    

